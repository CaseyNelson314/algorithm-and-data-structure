// キューを実装し、ラウンドロビンスケジューラのシミュレーションを行う企画

#include <iostream>



struct Process
{
    int pid;
    int time;
};

constexpr int n_buffer = 1204;
Process buffer[n_buffer];
int head;
int tail;

bool is_full()
{
    return (head + 1) % n_buffer == tail;
}

bool is_empty()
{
    return head == tail;
}

void enqueue(Process value)
{
    if (is_full())
        exit(1);

    buffer[head] = value;
    head = (head + 1) % n_buffer;
}

Process dequeue()
{
    if (is_empty())
        exit(1);
    Process value = buffer[tail];
    tail = (tail + 1) % n_buffer;
    return value;
}

#include <sstream>

int main()
{
    std::string input = R"(5 100
p1 150
p2 80
p3 200
p4 350
p5 20
)";

    std::istringstream is{ input };

    int n_proc;
    int timeslice;
    is >> n_proc >> timeslice;

    for (int i = 0; i < n_proc; ++i)
    {
        char nil;
        int pid;
        int time;
        is >> nil >> pid >> time;
        enqueue({ pid, time });
    }

    int runtime = 0;

    for (;;)
    {
        if (is_empty()) break;

        Process proc = dequeue();
        if (proc.time > timeslice)
        {
            proc.time -= timeslice;
            runtime += timeslice;
            enqueue(proc);
        }
        else
        {
            runtime += proc.time;
            std::cout << "p" << proc.pid << " " << runtime << std::endl;
        }
    }
}
