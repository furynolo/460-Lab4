// ucode.c file

char *cmd[]={"getpid", "ps", "chname", "kmode", "switch", "wait", "exit", "fork", "exec", 0};

int show_menu()
{
	printf("***************** Menu ********************************\n");
	printf("*  ps  chname  kmode  switch  wait  exit  fork  exec  *\n");
	printf("*******************************************************\n");
}

int find_cmd(char *name)
{
	int i=0;
	char *p = cmd[0];

	while (p)
	{
		if (strcmp(p, name)==0)
		{
			return i;
		}
		i++;
		p = cmd[i];
	}

	return(-1);
}

int getpid()
{
	return syscall(0,0,0);
}

int ps()
{
	return syscall(1, 0, 0);
}

int chname()
{
	int value;
	char s[64];
	printf("input new name : ");
	gets(s);
	value = syscall(2, s, 0);
	return value;
}

int kmode()
{
	int value;
	printf("kmode : syscall #3 to enter Kmode\n");
	printf("proc %d going K mode ....\n", getpid());
	value = syscall(3, 0, 0);
	printf("proc %d back from Kernel\n", getpid());
	return value;
}    

int kswitch()
{
	int value;
	printf("proc %d enter Kernel to switch proc\n", getpid());
	value = syscall(4,0,0);
	printf("proc %d back from Kernel\n", getpid());
	return value;
}

int wait()
{
	int child, exitValue;
	printf("proc %d enter Kernel to wait for a child to die\n", getpid());
	child = syscall(5, &exitValue, 0);
	printf("proc %d back from wait, dead child=%d", getpid(), child);
	if (child>=0)
		printf("exitValue=%d", exitValue);
	printf("\n");
	return exitValue;
} 

int exit()
{
	int exitValue;
	printf("\nenter an exitValue (0-9) : ");
	exitValue=(getc() &0x7F) - '0';
	printf("enter kernel to die with exitValue=%d\n", exitValue);
	_exit(exitValue);
	return exitValue;
}

int _exit(int exitValue)
{
	int value;
	value = syscall(6,exitValue,0);
	return value;
}

int getc()
{
	return syscall(90,0,0) &0x7F;
}

int putc(char c)
{
	return syscall(91,c,0,0);
}


int invalid(char *name)
{
	printf("Invalid command : %s\n", name);
	return (-1);
}

int fork()
{
	int value;
	value = syscall(7, 0, 0);
//	goUmode();
	return value;
}

int exec()
{
	int returnValue;

	char filename[64];
	printf("Enter filename:\t");
	gets(filename);
	printf("\n");
	returnValue = syscall(8, filename, 0);
	printf("exec() returned from kernel with value = %d.\n", returnValue);

	return returnValue;
}