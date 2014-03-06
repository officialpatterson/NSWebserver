typedef struct threadpool Threadpool;

Threadpool * createPool(int threads);

void addTaskToPool(Threadpool *pool, void (*routine)(void *),void *arg);

void destroy(Threadpool * pool);
