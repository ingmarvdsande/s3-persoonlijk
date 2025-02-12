//#include "stdafx.h"

#include <iostream>
#include <thread>
#include <mutex> 
#include <unistd.h> // for sleep.
using namespace std;

enum type_wenkbrauwen { w_lief, w_neutraal, w_boos };
enum type_ogen { o_open, o_dicht };
enum type_mond { m_open, m_dicht, m_boos };
type_wenkbrauwen wenkbrauwen = w_lief;
type_ogen		 ogen = o_open;
type_mond		 mond = m_dicht;
mutex mtx_wenkbrauwen;
mutex mtx_ogen;
mutex mtx_mond;

void wenkbrauwenController()
{
    while (true)
    {
        mtx_wenkbrauwen.lock();		// want mond gaan we hier schrijven.
        switch (wenkbrauwen) {
        case w_lief:wenkbrauwen = w_neutraal;	break;
        case w_neutraal:wenkbrauwen = w_boos;	break;
        default:wenkbrauwen = w_lief;	break;
        }
        mtx_wenkbrauwen.unlock();	// Dan kan ook de mondManager wenkbrauwen lezen.
        usleep(4000);		// verander eens per 4 sec.
    }
}

void mondController()
{
    while (true)
    {
        mtx_mond.lock();        // Lock mtx_mond first
        mtx_wenkbrauwen.lock(); // Then lock mtx_wenkbrauwen
        if (wenkbrauwen == w_boos) {
            mond = m_boos;
        }
        else // mond gaat open en dicht
        {
            switch (mond) {
            case m_open:mond = m_dicht;	break;
            default:mond = m_open;	break;
            }
        }
        mtx_wenkbrauwen.unlock();
        mtx_mond.unlock();
        usleep(500);            // update elke halve seconde
    }
}

void ogenController()
{
    while (true)
    {
        mtx_ogen.lock();		// want ogen gaan we hier schrijven.
        switch (ogen) {
        case o_open:ogen = o_dicht;	break;
        default:ogen = o_open;	break;
        }
        mtx_ogen.unlock();
        usleep(1000); // Add the sleep call here if needed
    }
}

void afbeeldTaak()
{
    while (true)
    {
        cout << endl << endl;
        mtx_wenkbrauwen.lock(); // Lock mtx_wenkbrauwen first
        switch (wenkbrauwen) {
        case w_boos:cout << "  \\   /" << endl;break;
        case w_lief:cout << "  /   \\" << endl;break;
        default:cout << "  w   w" << endl; break;
        }
        mtx_wenkbrauwen.unlock();

        mtx_ogen.lock();        // want uit ogen gaan we hier lezen.
        switch (ogen) {
        case o_open:cout << "  O   O" << endl;break;
        default:cout << "  _   _" << endl; break;
        }
        mtx_ogen.unlock();

        mtx_wenkbrauwen.lock(); // Lock mtx_wenkbrauwen first
        mtx_mond.lock();        // Then lock mtx_mond
        cout << "    U" << endl; // neus
        switch (mond) {
        case m_open:cout << "    O" << endl;break;
        case m_dicht:cout << "   ---";break;
        default:cout << "  /```\\" << endl; break;
        }
        mtx_mond.unlock();    
        mtx_wenkbrauwen.unlock();

        cout << endl << endl << endl;    // wat ruimte ertussen

        usleep(250);                // limiteer tot 4 gezichtjes per seconde.
                                    // dan zal de serial bus en de console het wel
                                    // bij kunnen houden.
    }
}

int main(int argc, char **argv) {
	thread t_wenkbrauwen(wenkbrauwenController);
	thread t_ogen(ogenController);
	thread t_mond(mondController);
	thread t_afbeelder(afbeeldTaak);
	t_wenkbrauwen.join();
	t_ogen.join();
	t_mond.join();
	t_afbeelder.join();
	return 0;
}

// abort has been called = serial buffer overflow

