#include <iostream>
#include <random>
#include <chrono>
#include <string>


int random_number();
std::string generate_hand();
void game_rules(std::string hand);



int main(){
    std::cout<<"==========================\nPIEDRA | PAPEL | TIJERA\n==========================\n";
    std::cout<<"[piedra, papel, tijera] >> ";

    std::string your_hand;
    std::cin>>your_hand;

    game_rules(your_hand);
    return 0;
}

void game_rules(std::string hand){
    std::string game_hand = generate_hand();
    if (hand==game_hand){
        std::cout<<"\nTHIS IS A TIE!"<<std::endl;
    }
    else if (
        hand=="piedra" && game_hand=="tijera" ||
        hand=="papel" && game_hand=="piedra" ||
        hand=="tijera" && game_hand=="papel"){
        std::cout<<"\nYOU WIN!"<<std::endl;
    }
    else{
        std::cout<<"\nYOU LOSE!"<<std::endl;
    }

    std::cout<<"try: "<<hand<<std::endl;
    std::cout<<"cpu: "<<game_hand<<std::endl;

}

std::string generate_hand(){
    static std::string hands[] = {"piedra","papel","tijera"};
    return hands[random_number()];
}

int random_number(){
    int time = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine engine(time);
    static std::uniform_int_distribution<int> distribution(0,2);
    return distribution(engine);
}