
#include <pthread.h>
#include <stdio.h>

/* The key used to associate a log le pointer with each thread. */
static pthread_key_t thread_log_key;

/* Write MESSAGE to the log le for the current thread. */
void write_to_thread_log(const char *message)
{
    FILE *thread_log = (FILE *)pthread_getspecific(thread_log_key);
    fprintf(thread_log, "%s\n", message);
}

/* Close the log le pointer THREAD_LOG. */
void close_thread_log(void *thread_log)
{
    fclose((FILE *)thread_log);
}
void *thread_function(void *args)
{
    char thread_log_filename[30];
    FILE *thread_log;
    /* Generate the lename for this thread’s log le. */
    sprintf(thread_log_filename, "thread%ld.log", (long)pthread_self());
    /* Open the log le. */
    thread_log = fopen(thread_log_filename, "w");
    /* Store the le pointer in thread-speci c data under thread_log_key. */
    pthread_setspecific(thread_log_key, thread_log);
    write_to_thread_log("Thread starting.");
    /* Do work here... */
    return NULL;
}

int main()
{
    int i;
    pthread_t threads[5];
    /* Create a key to associate thread log le pointers in
    thread-speci c data. Use close_thread_log to clean up
    the le pointers. */
    pthread_key_create(&thread_log_key, close_thread_log);
    /* Create threads to do the work. */
    for (i = 0; i < 5; ++i)
        pthread_create(&(threads[i]), NULL, thread_function, NULL);
    /* Wait for all threads to nish. */
    for (i = 0; i < 5; ++i)
        pthread_join(threads[i], NULL);
    return 0;
}