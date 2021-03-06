VFD=mtximage
echo compiling ......
	as86 -o ts.o  ts.s
	bcc  -c -ansi t.c
echo linking ......
	ld86 -d -o mtx ts.o t.o mtxlib /usr/lib/bcc/libc.a

echo cp mtx to /mnt/boot
	sudo mount -o loop $VFD /mnt
	sudo cp mtx /mnt/boot
	sudo umount /mnt
	sudo rm *.o mtx

(cd USER; ./mku u1 u2)

echo done
