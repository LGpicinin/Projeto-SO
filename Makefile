ppos_test5: ppos-core-aux.o pingpong-scheduler-srtf.o libppos_static.a
	gcc -o ppos_test5 ppos-core-aux.c pingpong-scheduler-srtf.c libppos_static.a