#!/bin/sh

mkdir -pv /iso-build/
mkdir -pv /mnt/iso
dd if=/dev/zero of=/iso-build/rootfs-sauzeros-live.img bs=1G seek=5 count=0
mkfs.f2fs /iso-build/rootfs-sauzeros-live.img
mount /iso-build/rootfs-sauzeros-live.img /mnt/iso
rsync -aAXHv --exclude={"/dev/*","/proc/*","/sys/*","/tmp/*","/run/*","/mnt/*","/root/*","/home/live/*","/usr/lib/modules/*","/usr/src/*","/iso-build/","/boot/*","/etc/fstab","/var/log/*"} / /mnt/iso
cat > /mnt/iso/home/live/.bashrc << "EOF"
#!/bin/sh

source /etc/profile

EOF

cat > /mnt/iso/home/live/.xinitrc << "EOF"
vmware-user-suid-wrapper &
exec dwm
EOF
cp /repo/kissD/extra/liveCD/wifi.txt /mnt/iso/home/live/
tar xvf /repo/kissD/extra/liveCD/google-chrome-config.tar.xz -C /mnt/iso/home/live/
chown -R live:live /mnt/iso/home/live/

umount /mnt/iso
