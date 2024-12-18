#define CATCH_CONFIG_MAIN // Просит Catch2 реализовать свой main, снимая эту задачу с разработчика

#include <catch2/catch.hpp>
//#include <catch2/internal/catch_decomposer.hpp>
#include <string>    
#include <sstream>
#include <compare>
#include "domino/simple_class.h"
#include "domino/difficult_class_static.h"
#include "domino/difficult_class_dynamic.h"

// Тестирование конструкторов
TEST_CASE("Domino") {
    SECTION("DefaultConstructor") {
    	srand(std::time(0));
        Simp::Domino d;
        REQUIRE(d.getTop() == 0);
        REQUIRE(d.getBot() == 0);
    }
    SECTION("InitConstructors") {
    	Simp::Domino d = Simp::Domino::rnd();
    	Simp::Domino dd;
		REQUIRE(d.getTop() < 7);
		REQUIRE(d.getBot() <7);
		REQUIRE(dd.getTop() == 0);
		REQUIRE(dd.getBot() == 0);
		Simp::Domino d1(2,5);
		Simp::Domino d2(6,0);
		REQUIRE(d1.getTop() == 2);
		REQUIRE(d1.getBot() == 5);
		REQUIRE(d2.getTop() == 6);
		REQUIRE(d2.getBot() == 0);
    }
    SECTION("TestException") {
        REQUIRE_THROWS(Simp::Domino(7, 9));
        REQUIRE_THROWS(Simp::Domino(1, -1));
    }

// Тестирование других методов
    SECTION("Setters") {
		Simp::Domino a;
		a.setTop(2);
		a.setBot(6);
		int x = 4;
		int y = 1;
		REQUIRE(a.getTop() == 2);
		REQUIRE(a.getBot() == 6);
		a.setTop(x);
		a.setBot(y);
		REQUIRE(a.getBot() == 1);
		REQUIRE(a.getTop() == 4);
		REQUIRE_THROWS(a.setTop(8));
		REQUIRE_THROWS(a.setBot(100));

    }
    SECTION("DominoMethods") {
		Simp::Domino a(1,5);
		Simp::Domino b;
		Simp::Domino c(0,0);
		Simp::Domino d(2,6);
		REQUIRE((b = a) == a);
		// REQUIRE((a<=>b) == std::strong_ordering::equal);
		// REQUIRE(a <=> c == std::strong_ordering::greater);
		// REQUIRE(a<=>d == std::strong_ordering::less);
		REQUIRE(a > c);
		REQUIRE(!(a > b or a < b));
		REQUIRE(a < d);
	//	REQUIRE((std::cin >> b) == a);
		b = a - b;
		REQUIRE(b.getTop() == 0);
		REQUIRE(b.getBot() == 0);
		b = a + d;
		REQUIRE(b.getTop() == 3);
		REQUIRE(b.getBot() == 4);
		b = a * d;
		REQUIRE(b.getTop() == 2);
		REQUIRE(b.getBot() == 2);
		b = d / a;
		REQUIRE(b.getTop() == 2);
		REQUIRE(b.getBot() == 1);
		REQUIRE_THROWS(d / c);
	//	std::stringstream::str(std::cout << "123\n");
	//	REQUIRE(std::stringstream::str(d.art(std::cout)) == "~~~~~~\n|* * |\n|    |\n|    |\n~~~~~\n|* * |\n|* * |\n|* * |\n~~~~~\n");
    	a.random();
    	REQUIRE(a.getTop() < 7);
    	REQUIRE(a.getBot() < 7);
        a.setTop(4);
        a.setBot(2);
        ~a;
        REQUIRE(a.getTop() == 2);
        REQUIRE(a.getBot() == 4);
        b = a;
        REQUIRE(b == a);
    }
    SECTION("Output and input"){
    	Simp::Domino d(3,6);
    	std::stringstream out;
    	d.art(out);
    	REQUIRE_NOTHROW(d.art(std::cout));
    	//REQUIRE(out.str == "~~~~~~\n|* * |\n|*   |\n|    |\n~~~~~~\n|* * |\n|* * |\n|* * |\n~~~~~~\n"); 
    	std::stringstream in("1\n5\n");
    	in >> d;
    	REQUIRE(d.getTop() == 1);
    	REQUIRE(d.getBot() == 5);
    }
}






TEST_CASE("GameStatic") {
    SECTION("DefaultConstructor") {
        DifS::Game g;
        REQUIRE(g.size() == 0);
        REQUIRE(g.capacity() == DifS::Game::capacity());
    }


    SECTION("StaticMethods") {
        DifS::Game g, gg1;
        DifS::Game ggg;
        DifS::Game lesser;
        Simp::Domino d(2,4);
        Simp::Domino dd(3,5);
       // Simp::Domino ddd();
       	for(size_t i = 0; i < 5; ++i){
       		lesser.push_back(dd);
       	}
       	REQUIRE(lesser.size() == 5);
       	REQUIRE(lesser.capacity() == DifS::Game::capacity());
        for(size_t i = 0; i < 10; ++i){
                g.push_back(d);
                gg1.push_back(dd);
                REQUIRE(g[i] == d);
                REQUIRE(gg1[i] == dd);
        }
        const DifS::Game gg = gg1;
        for(size_t i = 0; i < 10; ++i){
                REQUIRE(g.at(i) == d);
                REQUIRE(gg.at(i) == dd);
        }
        DifS::Game g2(30, true);
        REQUIRE(g2.size() == 30);
        REQUIRE_THROWS(g2.push_back(d));
        REQUIRE_THROWS(g.at(g.capacity()+1));
        REQUIRE_THROWS(gg.at(g.capacity()+1));
        DifS::Game all(1, false);
        int sum = 0;
        /*for(size_t i = 0; i < 7; ++i){
        	sum += i;
        	for(size_t j = i; j < 7; ++j){
        		REQUIRE(all[i*7 - sum + j].getTop() == i);
        		REQUIRE(all[i*7 - sum + j].getBot() == j);
			}
        }*/
        DifS::Game rand(6, true);
        for(size_t i = 0; i < rand.size(); ++i){
        	REQUIRE(rand[i].getTop() < 7);
        	REQUIRE(rand[i].getBot() < 7);
        }
        REQUIRE_THROWS(g.definite(100,1));
        REQUIRE_THROWS(g.definite(0,1));
        g += dd;
        REQUIRE(g.definite(3,5) == dd);
        REQUIRE_THROWS(g.del(100));
        g.del(5);
        REQUIRE(g.size() == 9);
        ggg = g;
        g.sorting();
        REQUIRE(ggg == g);
        ggg = g.find(2);
        REQUIRE(ggg == g); 
      }
      SECTION("Output and input"){
      	DifS::Game g;
      	Simp::Domino d(2,3);
      	for(int i = 0; i < 6; ++i){
      		g += d;
      	}
      	REQUIRE(g.size() == 6);
      	REQUIRE(g.capacity() == DifS::Game::capacity());
	  	std::stringstream out;
	  	out << g;
	  	REQUIRE_NOTHROW(std::cout << g);
	  	//REQUIRE(out.str == "(2;3),(2;3),(2;3),(2;3),(2;3),(2;3),\n");
	  	g.print(out, "ABOBA\n");
	  	REQUIRE_NOTHROW(g.print(std::cout, "ABOBA"));
	  	//REQUIRE(out.str == "ABOBA\n(2;3),(2;3),(2;3),(2;3),(2;3),(2;3),\n");	  
	  	std::stringstream in("4\n2\n3\n3\n4\n4\n5\n5\n6\n");
	  	in >> g;
	  	REQUIRE(g.size() == 4);
	  	REQUIRE(g.capacity() == DifS::Game::capacity()); 
	  	REQUIRE(g[0].getTop() == 2);
	  	REQUIRE(g[0].getBot() == 3); 
	  	REQUIRE(g[1].getTop() == 3);
	  	REQUIRE(g[1].getBot() == 4);
	  	REQUIRE(g[2].getTop() == 4);
	  	REQUIRE(g[2].getBot() == 5);
	  	REQUIRE(g[3].getTop() == 5);
	  	REQUIRE(g[3].getBot() == 6);  	
      }
      SECTION("Static getters"){
      	DifS::Game g(true, 9);
      	REQUIRE(g.size() == 1);
      	REQUIRE(g.capacity() == DifS::Game::capacity());
      }


	SECTION("Static operators"){
		DifS::Game g, gg1;
		DifS::Game ggg;
		DifS::Game lesser;
		Simp::Domino d(2,4);
		Simp::Domino dd(3,5);
		for(size_t i = 0; i < 5; ++i){
	    	lesser.push_back(dd);
	    }
	    REQUIRE(lesser.size() == 5);
	    REQUIRE(lesser.capacity() == DifS::Game::capacity());
		for(size_t i = 0; i < 10; ++i){
			g.push_back(d);
	    	gg1.push_back(dd);
		    REQUIRE(g[i] == d);
		    REQUIRE(gg1[i] == dd);
 	    }
 	    const DifS::Game gg = gg1;
		+g;
        for(size_t i = 0; i < 10; ++i){
                REQUIRE(g[i] == dd);
        }
        -g;
        for(size_t i = 0; i < 10; ++i){
                REQUIRE(g[i] == d);
        }
        d.setTop(4); d.setBot(2);
        !g;
        for(size_t i = 0; i < g.size(); ++i){
                REQUIRE(g[i] == d);
        }
        DifS::Game g1(30, true);
        REQUIRE_THROWS(gg + g1);
        ggg = ggg + g;
        for(size_t i = 0; i < ggg.size(); ++i){
                REQUIRE(ggg[i] == d);
        }
        REQUIRE_THROWS(lesser - ggg);
        g = ggg - lesser;
        for(size_t i = 0; i < 5; ++i){
                REQUIRE(g[i].getTop() == 1);
                REQUIRE(g[i].getBot() == 0);
        }
        REQUIRE_THROWS(lesser*ggg);
        REQUIRE_NOTHROW(g = g*ggg);
        /*for(size_t i = 0; i < g.size(); ++i){
                REQUIRE(g[i].getTop() == 2);
                REQUIRE(g[i].getBot() == 0);
        }*/
        REQUIRE_THROWS(lesser/ggg);
        +g;
        REQUIRE_NOTHROW(g = g/gg);
        /*for(size_t i = 0; i < g.size(); ++i){
                REQUIRE(g[i].getTop() == 1);
                REQUIRE(g[i].getBot() == 0);
        }*/
		+g;
		REQUIRE_NOTHROW(ggg /= g);
		/*for(size_t i = 0; i < ggg.size(); ++i){
			REQUIRE(ggg[i].getTop() == 2);
			REQUIRE(ggg[i].getBot() == 2);
		}*/
		REQUIRE_NOTHROW(ggg *= g);
		/*for(size_t i = 0; i < ggg.size(); ++i){
			REQUIRE(ggg[i].getTop() == 4);
			REQUIRE(ggg[i].getBot() == 2);
		}*/	
		REQUIRE_NOTHROW(ggg -= g);
		/*for(size_t i = 0; i < ggg.size(); ++i){
			REQUIRE(ggg[i].getTop() == 2);
			REQUIRE(ggg[i].getBot() == 1);
		}*/
		REQUIRE_NOTHROW(ggg += g);
		/*for(size_t i = 0; i < ggg.size(); ++i){
			REQUIRE(ggg[i].getTop() == 4);
			REQUIRE(ggg[i].getBot() == 2);
		}*/
		REQUIRE(ggg > g);
		REQUIRE(ggg < gg);
		REQUIRE(ggg == ggg);
		REQUIRE(ggg.sum() == 60);
		g += d;
		REQUIRE(g[g.size()-1] == d);
		g++;
		REQUIRE(g[g.size()-1].getTop() < 7);
		REQUIRE(g[g.size()-1].getBot() < 7);
		++g;
		REQUIRE(g[g.size()-1].getTop() < 7); 
		REQUIRE(g[g.size()-1].getBot() < 7);
		Simp::Domino tmp = ~g;
		REQUIRE(tmp.getTop() < 7);
		REQUIRE(tmp.getBot() < 7);
			
	}
}




TEST_CASE("GameDynamic") {
    SECTION("DefaultConstructor") {
        DifD::Game g;
        REQUIRE(g.size() == 0);
        REQUIRE(g.capacity() == 0);
        DifD::Game gg(8, true);
        REQUIRE(gg.size() == 8);
        DifD::Game ggg(3, false);
        REQUIRE(ggg.size() == 3*28);
        DifD::Game cop(std::move(ggg));
        REQUIRE(cop.size() == 28*3);
        REQUIRE(ggg.size() == 0);
        REQUIRE(ggg.capacity() == 0);
        cop = gg;
        REQUIRE(cop.size() == 8);
        cop = std::move(gg);
        REQUIRE(cop.size() == 8);
        REQUIRE(gg.size() == 0);
        REQUIRE(gg.capacity() == 0);
        DifD::Game n(23);
        REQUIRE(n.size() == 0);
        REQUIRE(n.capacity() == 23);
    }

    SECTION("DynamicMethods") {
        DifD::Game g, gg1;
        DifD::Game ggg;
        DifD::Game lesser;
        Simp::Domino d(2,4);
        Simp::Domino dd(3,5);
        for(size_t i = 0; i < 5; ++i){
                lesser.push_back(dd);
                REQUIRE(lesser[i] == dd);
        }
        REQUIRE(lesser.size() == 5);
        //REQUIRE(lesser.capacity() == DifS::Game::capacity());
        for(size_t i = 0; i < 10; ++i){
                g.push_back(d);
                gg1.push_back(dd);
                REQUIRE(g[i] == d);
                REQUIRE(gg1[i] == dd);
        }
        const DifD::Game gg = gg1;
        for(size_t i = 0; i < 10; ++i){
                REQUIRE(g.at(i) == d);
                REQUIRE(gg.at(i) == dd);
        }
        REQUIRE_THROWS(g.at(g.capacity()+1));
        REQUIRE_THROWS(gg.at(g.capacity()+1));
       	REQUIRE(lesser.sum() == 40);
       	lesser.shift_l(2);
       	REQUIRE(lesser.size() == 4);
       	lesser += d;
       	Simp::Domino tmp = lesser.definite(2,4);
       	REQUIRE(tmp == d);
       	REQUIRE(lesser.size() == 4);
       	g.del(5);
       	REQUIRE(g.size() == 9);
       	DifD::Game rand(20, true);
       	REQUIRE_NOTHROW(rand.sorting());
       	//for(size_t i = 0; i < rand.size()-1; ++i){
       	//	REQUIRE((rand[i] < rand[i+1])) || (rand[i] == rand[i+1]));
       	//}
       	rand = g.find(2);
       	REQUIRE(rand.size() == 9);
		REQUIRE_THROWS(rand.del(100));
		REQUIRE_THROWS(rand.definite(21,3));
      }
      SECTION("Output and input(dynamic)"){
        DifD::Game g;
        Simp::Domino d(2,3);
        for(int i = 0; i < 6; ++i){
                g += d;
        }
        REQUIRE(g.size() == 6);
        std::stringstream out;
        out << g;
        REQUIRE_NOTHROW(std::cout << g);
       // REQUIRE(out.str == "(2;3),(2;3),(2;3),(2;3),(2;3),(2;3),\n");
        g.print(out, "ABOBA\n");
        REQUIRE_NOTHROW(g.print(std::cout, "ABOBA"));
       // REQUIRE(out.str == "ABOBA\n(2;3),(2;3),(2;3),(2;3),(2;3),(2;3),\n");
        std::stringstream in("4\n2\n3\n3\n4\n4\n5\n5\n6\n");
        in >> g;
        REQUIRE(g.size() == 4);
        REQUIRE(g[0].getTop() == 2);
        REQUIRE(g[0].getBot() == 3);
        REQUIRE(g[1].getTop() == 3);
        REQUIRE(g[1].getBot() == 4);
        REQUIRE(g[2].getTop() == 4);
        REQUIRE(g[2].getBot() == 5);
        REQUIRE(g[3].getTop() == 5);
        REQUIRE(g[3].getBot() == 6);
      }
      SECTION("Dyanamic getters"){
        DifD::Game g(true, 9);
        REQUIRE(g.size() == 1);
        DifD::Game gg(12);
        REQUIRE(gg.capacity() == 12);
      }


        SECTION("Dynamic operators"){
            DifD::Game g, gg1;
            DifD::Game ggg;
            DifD::Game lesser;
            Simp::Domino d(2,4);
            Simp::Domino dd(3,5);
            for(size_t i = 0; i < 5; ++i){
              	lesser.push_back(dd);
            }
            REQUIRE(lesser.size() == 5);
            for(size_t i = 0; i < 10; ++i){
                g.push_back(d);
                gg1.push_back(dd);
                REQUIRE(g[i] == d);
                REQUIRE(gg1[i] == dd);
            }
        const DifD::Game gg = gg1;    
        +g;
        for(size_t i = 0; i < 10; ++i){
                REQUIRE(g[i] == dd);
        }
        -g;
        for(size_t i = 0; i < 10; ++i){
                REQUIRE(g[i] == d);
        }
        d.setTop(4); d.setBot(2);
        !g;
        for(size_t i = 0; i < g.size(); ++i){
                REQUIRE(g[i] == d);
        }
        ggg = ggg + g;
        REQUIRE(ggg.size() == 10);
        REQUIRE_THROWS(lesser - ggg);
        g = ggg - lesser;
        for(size_t i = 0; i < 5; ++i){
                REQUIRE(g[i].getTop() == 1);
                REQUIRE(g[i].getBot() == 0);
        }
        REQUIRE_THROWS(lesser*ggg);
        REQUIRE_NOTHROW(g = g*ggg);
        /*for(size_t i = 0; i < g.size(); ++i){
                REQUIRE(g[i].getTop() == 2);
                REQUIRE(g[i].getBot() == 0);
        }*/
        REQUIRE_THROWS(lesser/ggg);
        //REQUIRE_NOTHROW()
        +g;
        REQUIRE_NOTHROW(g = g/gg);
        /*for(size_t i = 0; i < g.size(); ++i){
                REQUIRE(g[i].getTop() == 1);
                REQUIRE(g[i].getBot() == 1);
        }*/
        +g;
        REQUIRE_NOTHROW(ggg /= g);
        /*for(size_t i = 0; i < ggg.size(); ++i){
            REQUIRE(ggg[i].getTop() == 2);
            REQUIRE(ggg[i].getBot() == 2);
        }*/
        DifD::Game ab(10, true); 
        REQUIRE_NOTHROW(ab *= g);
        /*for(size_t i = 0; i < ggg.size(); ++i){
            REQUIRE(ggg[i].getTop() == 4);
            REQUIRE(ggg[i].getBot() == 2);
        }*/
        REQUIRE_NOTHROW(ab -= g);
        /*for(size_t i = 0; i < ggg.size(); ++i){
            REQUIRE(ggg[i].getTop() == 2);
            REQUIRE(ggg[i].getBot() == 1);
        }*/
        REQUIRE_NOTHROW(ab += g);
        /*for(size_t i = 0; i < ggg.size(); ++i){
            REQUIRE(ggg[i].getTop() == 4);
            REQUIRE(ggg[i].getBot() == 2);
        }*/
        
        REQUIRE_THROWS((ggg > g));
        REQUIRE_THROWS(ggg < gg);
        REQUIRE_THROWS(ggg == g);
        REQUIRE(ggg == ggg);
        DifD::Game dp, dn;
        Simp::Domino l(0,1), ll(5,6);
        for(int i = 0; i < 10; ++i){
        	dp.push_back(ll);
        	dn.push_back(l);
        }
        REQUIRE(dp > g);
        REQUIRE(dn < g);
        REQUIRE(ggg.sum() != 60);
        g += d;
        REQUIRE(g[g.size()-1] == d);
        g++;
        REQUIRE(g[g.size()-1].getTop() < 7);
        REQUIRE(g[g.size()-1].getBot() < 7);
        ++g;
        REQUIRE(g[g.size()-1].getTop() < 7);
        REQUIRE(g[g.size()-1].getBot() < 7);
        Simp::Domino tmp = ~g;
        REQUIRE(tmp.getTop() < 7);
        REQUIRE(tmp.getBot() < 7);

        }
}
