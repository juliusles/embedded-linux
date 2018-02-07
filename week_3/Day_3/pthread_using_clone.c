extern errno;
void*
f(void *arg)
{
    printf("%u,%p\n", getpid(), &errno);
    fflush(stdin);
    return NULL;
}

int
main(int argc, char **argv)
{
    pthread_t tid;
    pthread_create(&tid, NULL, f, NULL);
    printf("%u,%p\n", getpid(), &errno);
    fflush(stdin);
    pthread_join(tid, NULL);
    return 0;
}