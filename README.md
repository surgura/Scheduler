# Scheduler
A basic fifo scheduler template made as an exercise for myself. 
Run the scheduler and add tasks asynchronously. 
Spins while no tasks are available for the case of simplicity. 

Depends on liblfds for lockless queue and lockless memory pool. 

Additional test/example project is available, which uses winsock2 to multitask sockets and other work.
The test is windows-only, but the scheduler is not. 
