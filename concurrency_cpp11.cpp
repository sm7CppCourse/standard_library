#include <queue>               // std::queue
#include <string>              // std::string
#include <condition_variable>  // std::condition_variable
#include <thread>              // std::thread, std::this_thread
#include <mutex>               // std::mutex, std::lock_guard
#include <crono>               // std::chrono::milliseconds
#include <iostream>

using namespace std;

bool g_work = true;
queue<string> message_queue;

// Мьютекс (mutex) - основной объект синхронизации потоков в C++11
// Перед работой с общими для нескольких потоков данными, мьютекс должен быть 
// заблокирован методом lock,а после окончания работы с общими данными — 
// разблокирован методом unlock.
mutex g_queue_mutex;

// Условная переменная (condition_variable) - объект синхронизации, который
// позволяет блокировать один или несколько потоков, пока не будет получено 
// уведомление от другого потока.
condition_variable g_condition;


void producer_func(int number)
{
	for(int i=0; i< 10; i++)
	{
	    // Имитируем нагрузку - спим случайное количство мс.
	    // во время "сна" поток отдает кванты своего процессорного времени
	    // другим потокам.
	    this_thread::sleep_for(chrono::milliseconds(rand() % 100));	    
	    
	    {
	        // Блокируем мьютекс. После этого мы можем быть уверены, что
	        // только один поток в одно время изменяет очередь.
	        
    	        // Объект lock_guard при создании пытается получить мьютекс (вызывая lock()), 
    	        // а при уничтожении автоматически освобождает мьютекс (вызывая unlock())
    		lock_guard<mutex> lock(g_queue_mutex);
    		
    		// Кладем сообщение в очередь
    		auto message = "Producer " + to_string(number) + " send message #" + to_string(i);
    		message_queue.push(message);
	    }
	
	    g_condition.notify_all();
	}
}

class Consumer
{
public:

    void operator()()
    {
        // Объект unique_lock схож с lock_guard но имеет более широкий интерфейс	    
    	unique_lock<mutex> lock(g_queue_mutex);    
        
        // поток будет работать до тех пор пока функция не завершится,
        // т.е. пока не завершится цикл когда g_work станет = false
    	while(g_work)
    	{
    	    // Метод wait условной переменной разблокирует mutex, давая другим 
    	    // потокам выполнить их работу и блокирует текущий поток до 
    	    // наступления события (вызова метода notify_all(one) другим потоком).
    	    // Затем блокирует mutex вновь, позволяя текущему потоку обработать 
    	    // событие.
    	    
    	    // Метод wait имеет также одну особенность - он может завершиться
    	    // и без внешнего сигнала, поэтому вызываем его в цикле с проверкой
    	    // а действительно ли в очереди появились данные.
    	    g_condition.wait(lock);
    		
    	    while(!message_queue.empty())
    	    {
    	        // Обрабатываем данные - в данном случае просто выводим на консоль.
    	        cout << message_queue.front() << endl;
    	        message_queue.pop();
    	    }
    	}
    }
};


void concurrency_Cpp11()
{
    srand(time(0));
    
    //-- Запускаем 5 потоков, которые параллельно шлют данные в очередь
    vector<thread> producers;
    for(int i=0; i<5; ++i)
    {
        // чтобы начать выполнение потока создаем объект thread
        // и передаем название функции, которая будет в этом потоке 
        // выполняться и ее параметры. 
        // объект thread хранит лишь идентификатор потока в системе,
        // поэтому может быть скопирован без последствий
        producers.push_back(thread(producer_func, i));
    }

    // Запускаем поток, который обрабатывает данные из очереди
    g_work = true;    
    // вместо фукции thread может принимать в конструкторе функциональный объект
    auto consumer = thread(Сonsumer());

    for(int i=0; i<5; ++i)
    {
        // Ждем пока завершатся все потоки-генераторы
        producers[i].join();      
    }

    // Устанавливаем флаг g_work в false, чтобы прервать цикл и 
    // ждем пока завершится поток-получатель
    g_work = false;	
    consumer.join();
}
