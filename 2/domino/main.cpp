#include <iostream>
#include <ostream>
#include <cstring>
#include <ctime>
#include "simple_class.h"
#include "difficult_class_static.h"
#include "difficult_class_dynamic.h"

using namespace Simp;

#ifdef DIF_S
using namespace DifS;
#endif DIF_S

#ifdef DIF_D
using namespace DifD;
#endif DIF_D

int main() {
	srand(std::time(0));
    try {
        while (true) {
        
 #ifdef  DIF_D
            Game g;
            int t;
            bool flag = true;
            std::cout << "Choose type of constructor \"Game\"" << '\n';
            std::cout << " 1.Default\n" << " 2.Random\n" << " 3.All kinds of\n" << " 4.Exit\n" << ">>";
            t = getNum<int>(1, 4);
            switch (t) {
                case 1:
                    break;
                case 2: {
                    std::cout << "Enter number of elements >>";
                    int num = getNum<int>(0);
                    Game gg(num, true);
                    g = gg;
                    g.print(std::cout);
                    break;
                }
                case 3: {
                    std::cout << "Enter number of elements >>";
                    int num = getNum<int>(0);
                    Game gg(num, false);
                    g = gg;
                    g.print(std::cout);
                    break;
                }
                default:
                    return 0;
            }
            // then we are working with g
            while (flag) {
                std::cout << "Choose type of method \"Game\"" << '\n';
                std::cout << " 1.Add definite \"Domino\" \n" << " 2. Add random \"Domino\" \n"
                          << " 3.Get definite \"Domino\"\n" << " 4.Get random \"Domino\"\n"
                          << " 5.Equate to \"= \" \n" << " 6.Delete \"Domino\" by number\n" << " 7.Sorting\n"
                          << " 8. Find subset with set value top or bottom\n" << " 9.Delete \"Game\"\n"
                          << " 10. Print\n" << " 11. Exit\n"
                          << ">>";
                t = getNum<int>(1, 11);
                Game gg;
                Domino d;
                switch (t) {
                    case 1: {
                        d = new_d();
                        g += d;
                        break;
                    }
                    case 2: {
                        ++g;
                        break;
                    }
                    case 3: {
                        d = new_d();
                        d = g.definite(d.getTop(), d.getBot());
                        d.art(std::cout);
                        break;
                    }
                    case 4: {
                        d = ~g;
                        d.art(std::cout);
                        break;
                    }
                    case 5: {
                        Game gg(10, true);
                        g = gg;
                        break;
                    }
                    case 6: {
                        std::cout << "Enter number of \"Domino\" >>";
                        int ptr = getNum<int>(1);
                        g.del(ptr);
                        break;
                    }
                    case 7: {
                        g.sorting();
                        break;
                    }
                    case 8: {
                        std::cout << "Enter value of top or bottom in \"Domino\" >>\n";
                        int v = getNum<int>(0, 6);
                        Game gg = g.find(v);
                        gg.print(std::cout, "--------------------Found subset----------------------\n");
                        break;
                    }

                    case 9: {
                        //g.~Game();
                        flag = false;
                        break;
                    }
                    case 10: {
                    	std::cout << g;
                        break;
                    }
                    default:
                        return 0;
                }
                g.print(std::cout, "------------------------Made \"Game\"---------------------\n");
            }

#endif DIF_D 

#ifdef DIF_S
            Game g;
            int t;
            bool flag = true;
            std::cout << "Choose type of constructor \"Game\"" << '\n';
            std::cout << " 1.Default\n" << " 2.Random\n" << " 3.All kinds of\n" << " 4.Exit\n" << ">>";
            t = getNum<int>(1, 4);
            switch (t) {
                case 1:
                    break;
                case 2: {
                    std::cout << "Enter number of elements >>";
                    int num = getNum<int>(0);
                    Game gg(num, true);
                    g = gg;
                    g.print(std::cout);
                    break;
                }
                case 3: {
                    std::cout << "Enter number of elements >>";
                    int num = getNum<int>(0);
                    Game gg(num, false);
                    g = gg;
                    g.print(std::cout);
                    break;
                }
                default:
                    return 0;
            }
            // then we are working with g
            while (flag) {
                std::cout << "Choose type of method \"Game\"" << '\n';
                std::cout << " 1.Add definite \"Domino\" \n" << " 2. Add random \"Domino\" \n"
                          << " 3.Get definite \"Domino\"\n" << " 4.Get random \"Domino\"\n"
                          << " 5.Equate to \"= \" \n" << " 6.Delete \"Domino\" by number\n" << " 7.Sorting\n"
                          << " 8. Find subset with set value top or bottom\n" << " 9.Delete \"Game\"\n"
                          << " 10. Print\n" << " 11. Exit\n"
                          << ">>";
                t = getNum<int>(1, 11);
                Game gg;
                Domino d;
                switch (t) {
                    case 1: {
                        d = new_d();
                        g += d;
                        break;
                    }
                    case 2: {
                        ++g;
                        break;
                    }
                    case 3: {
                        d = new_d();
                        d = g.definite(d.getTop(), d.getBot());
                        d.art(std::cout);
                        break;
                    }
                    case 4: {
                        d = ~g;
                        d.art(std::cout);
                        break;
                    }
                    case 5: {
                        Game gg(gg.capacity(), true);
                        g = gg;
                        break;
                    }
                    case 6: {
                        std::cout << "Enter number of \"Domino\" >>";
                        int ptr = getNum<int>(1);
                        g.del(ptr);
                        break;
                    }
                    case 7: {
                        g.sorting();
                        break;
                    }
                    case 8: {
                        std::cout << "Enter value of top or bottom in \"Domino\" >>\n";
                        int v = getNum<int>(0, 6);
                        Game gg = g.find(v);
                        gg.print(std::cout, "--------------------Found subset----------------------\n");
                        break;
                    }

                    case 9: {
                        //g.~Game();
                        flag = false;
                        break;
                    }
                    case 10: {
                        std::cout << g;
                        break;
                    }
                    default:
                        return 0;
                }
                g.print(std::cout, "------------------------Made \"Game\"---------------------\n");
            }
#endif DIF_S

#ifdef SIMP

        Domino d;
        int t;
        bool flag = true;
        std::cout << "Choose type of constructor \"Domino\"" << '\n';
        std::cout << " 1.Default\n" << " 2.Random\n" << " 3.Optional\n" << " 4.Exit\n" <<">>";
        t = getNum<int>(1, 4);
        switch(t) {
            case 1:
                break;
            case 2:{
            	Domino e = Domino::rnd();
                d = e;
                break;
            }
            case 3: {
                std::cout << "Enter number of upper part >>";
                auto l = getNum<size_t>(0, 6);
                std::cout << "Enter number of lower part >>";
                auto b = getNum<size_t>(0, 6);
                Domino e(l, b);
                d = e;
                break;
            }
            default:
                return 0;
        }
        // then we are working with d
        while(flag) {
            std::cout << "Choose type of method \"Domino\"" << '\n';
            std::cout << " 1.Random\n" << " 2.\"~\"(Rotate) \n" << " 3.Art\n" << " 4.Equate to\n" << " 5.Compare with\n"
                      << " 6.Change\n" << " 7.Delete\n" << " 8. Exit\n" << ">>";
            t = getNum<int>(1, 8);
            Domino b;
            switch (t) {
                case 1:
                    d.random();
                    break;
                case 2:
                    ~d;
                    break;
                case 3:
                    d.art(std::cout);
                    break;
                case 4:
                    d = new_d();
                    break;
                case 5:
                    b = new_d();
                    if (b == d)
                        std::cout << "Equal\n";
                    else
                        std::cout << "Non Equal\n";
                    break;
                case 6:
                    b = new_d();
                    d = b;
                    break;
                case 7:
                    d.~Domino();
                    flag = false;
                    break;
                default:
                    return 0;
            }
        }
    #endif SIMP
    }
    }
    catch(const std::bad_alloc &ba) { // в случае ошибок выделения памяти
        std::cerr << "Not enough memory" << std::endl;
        return 1;
    }
    catch(const std::exception &e) { // в случае прочих исключений
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

