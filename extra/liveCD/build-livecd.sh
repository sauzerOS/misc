#!/bin/sh
export KERNVER=5.13.0-sauzeros-live
export VER=5.13
export ROOTFSIMAGE=rootfs-sauzeros-live.img

mkdir -vp /mnt/iso

#build an initramfs with dracut and extract it to /usr/src/initramfs
dracut -m "base drm bash" -f /iso-build/initramfs.img $KERNVER

cd /iso-build/
mkdir initramfs
pushd initramfs
lsinitrd --unpack ../initramfs.img
rm init
cd lib
rm -rf firmware
popd

#copy modules to initramfs
#rm -rf lib/modules/*
#cp -a /lib/modules/$KERNVER lib/modules/

#copy modules to rootfs
mount $ROOTFSIMAGE /mnt/iso
rm -rf /mnt/iso/lib/modules/*
cp -a /lib/modules/$KERNVER /mnt/iso/lib/modules/
umount /mnt/iso

cp -v /usr/bin/switch_root /iso-build/initramfs/usr/bin/
mkdir -v /iso-build/initramfs/boot
echo "sauzeros-live" > /iso-build/initramfs/boot/id_label

cat > /iso-build/initramfs/init << "EOF"
#!/bin/sh

mount -t proc none /proc
mount -t sysfs none /sys
mount -t devtmpfs none /dev

ARCH=x86_64
LABEL="$(cat /boot/id_label)"


#load driver early for miix-sg80
modprobe pwm-lpss
modprobe pwm-lpss-platform
modprobe drm
modprobe i915

###########################
rescue_shell() {
exec sh
}
###########################

overlayMount() {

mkdir -p /mnt/writable
mount -t tmpfs -o rw tmpfs /mnt/writable
mkdir -p /mnt/writable/upper
mkdir -p /mnt/writable/work

D_LOWER="/mnt/system"
D_UPPER="/mnt/writable/upper"
D_WORK="/mnt/writable/work"
OVERLAYFSOPT="lowerdir=${D_LOWER},upperdir=${D_UPPER},workdir=${D_WORK}"

mount -t overlay overlay -o ${OVERLAYFSOPT} ${ROOT} 

}
###########################

mkdir -p /mnt/medium
mkdir -p /mnt/system
mkdir -p /mnt/rootfs

sleep 3

# Search for, and mount the boot medium
LABEL="$(cat /boot/id_label)"
for device in $(ls /dev/); do

    [ "${device}" == "console" ]  && continue
    [ "${device}" == "null"    ]  && continue
    [ "${device}" == "snapshot" ] && continue
    [ "${device}" == "port" ]     && continue
    [ "${device}" == "random" ]   && continue
    [[ "${device}" == tty* ]]     && continue
    [[ "${device}" == loop* ]]    && continue

    echo $device && mount -o ro /dev/${device} /mnt/medium 2> /dev/null && \
    if [ "$(cat /mnt/medium/boot/${ARCH}/id_label)" != "${LABEL}" ]; then
        umount /mnt/medium
    else
        DEVICE="${device}"
        break
    fi
done

if [ "${DEVICE}" == "" ]; then
    echo "STOP: Boot medium not found."
    rescue_shell
fi

# Mount the system image
mount -t squashfs -o ro,loop /mnt/medium/boot/${ARCH}/root.sfs /mnt/system || {
    if [ -r /mnt/medium/boot/${ARCH}/root.sfs ]; then
        echo "STOP: Unable to mount system image. The kernel probably lacks"
        echo "      SquashFS support. You may need to recompile it."
    else
        echo "STOP: Unable to mount system image. It seems to be missing."
    fi

    rescue_shell
}

# Define where the new root filesystem will be
ROOT="/mnt/rootfs" # Also needed for /usr/share/live/sec_init.sh

# Select LiveCD mode
overlayMount

# Move current mounts to directories accessible in the new root
cd /mnt
for dir in $(ls -1); do
    if [ "${dir}" != "rootfs" ]; then
        mkdir -p ${ROOT}/mnt/.boot/${dir}
        mount --move /mnt/${dir} ${ROOT}/mnt/.boot/${dir}
    fi
done
cd /

exec switch_root ${ROOT} /sbin/init

EOF

pushd initramfs
chmod +x init

find . -print0 | cpio --null -ov --format=newc > ../initramfs-livecd
popd
rm -rf initramfs

lz4 -flv initramfs-livecd

mount -o loop,ro $ROOTFSIMAGE /mnt/iso
mksquashfs /mnt/iso/ root.sfs -comp xz
umount /mnt/iso

tar xvf /repo/kissD/extra/liveCD/livecd-structure.tar.xz -C .

cp /usr/src/linux-$VER/arch/x86/boot/bzImage .
echo "sauzeros-live" > live/boot/x86_64/id_label
mv -vf root.sfs live/boot/x86_64
cp -vf initramfs-livecd.lz4 live/boot/x86_64/initram.fs
cp -vf bzImage live/boot/x86_64/vmlinuz-sauzeros
mount live/EFI/sauzeros/efiboot.img /mnt/iso
cp -vf initramfs-livecd.lz4 /mnt/iso/initram.fs
cp -vf bzImage /mnt/iso/vmlinuz-sauzeros
umount /mnt/iso

rm -f bzImage initramfs.img initramfs-livecd initramfs-livecd.lz4

xorriso -as mkisofs \
       -iso-level 3 \
       -full-iso9660-filenames \
       -volid "sauzeros" \
       -eltorito-boot isolinux/isolinux.bin \
       -eltorito-catalog isolinux/boot.cat \
       -no-emul-boot -boot-load-size 4 -boot-info-table \
       -isohybrid-mbr live/isolinux/isohdpfx.bin \
       -eltorito-alt-boot \
       -e EFI/sauzeros/efiboot.img \
       -no-emul-boot -isohybrid-gpt-basdat \
       -output sauzeros-live.iso \
	live

rm -rf live

echo "all done"
