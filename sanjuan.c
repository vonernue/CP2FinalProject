#include "sanjuan.h"

const string cardNameData[2][30] = 
    {{"\033[0;35mIndigo plant\033[0m", "\033[0;33mSugar Mill\033[0m", "\033[0;32mTobacco storage\033[0m",
    "\033[0;34mCoffee Roaster\033[0m", "\033[0;36mSilver smelter\033[0m",
    "Tower", "Chapel", "Smithy", "Poor House", "Black Market", "Crane", "Carpenter",
    "Quarry", "Well", "Aqueduct", "Market Stand", "Market Hall", "Trading Post", "Archive",
    "Perfecture", "Gold mine", "Library", "Statue", "Victory Column", "Hero", "Guild Hall", "City Hall",
    "Triumhal Arch", "Palace"},
    {"\033[0;35m染料廠\033[0m", "\033[0;33m蔗糖廠\033[0m", "\033[0;32m菸草廠\033[0m", "\033[0;34m咖啡廠\033[0m", "\033[0;36m白銀廠\033[0m", "塔樓", "禮拜堂", "鐵匠鋪", "救濟院",
    "黑市", "起重機", "木工場", "採石場", "水井", "溝渠", "攤販", "市場", "交易所", "檔案館", "辦公處", "金礦坑", "圖書館",
    "雕鑄像紀念碑", "勝利柱紀念碑", "英雄像紀念碑", "同業會館", "市政廳", "凱旋門", "宮殿"}};

const string roleName[2][5] = {{"Builder", "Producer", "Trader", "Councilor", "Prosoector"}, {"建築師", "生產者", "商人", "市長", "淘金者"}};
const string roleDescription[2][5] = {{"Action\nStart from governor's left,clock wise.Player can choose to build a building and pay the card cost\n\nPrivilege\nGovernor can pay 1 less of the cost. The final cost can't lower than 1 cost.\n",
                                        "Action\nStart from governor's left,clock wise.Player can choose produce 1 product.\n\nPrivilege\nGovernor can product an extra product.\n",
                                        "Action\nStart from governor's left,clock wise.Player can sell 1 product.\n\nPrivilege\nGovernor can sell an extra product.\n\nFlip 1 price list.\nThe product's value depents on the list.\n",
                                        "Action\nStart from governor's left,clock wise.Player can draw 2 cards and keep one.\n\nPrivilege\nGovernor can draw 5 cards and keep one\n",
                                        "Action\nNone.\n\nPrivilege\nGovernor can draw 1 card.\n"},
                                        {"行動\n從總督左邊開始，順時鐘方向，玩家選擇1張欲建造的建築卡，並支付卡片費用。\n\n特權\n總督在建造時，可以少支付1個費用，但最後的費用不能少於1。\n",
                                        "行動\n從總督左邊開始，順時鐘方向，玩家可以生產1個貨品。\n\n特權\n總督可以多生產1個貨品。\n",
                                        "行動\n從總督左邊開始，順時鐘方向，玩家可以販賣1個貨品。\n\n特權\n總督可以多販賣1個貨品。\n\n翻開1張價目表，貨品價格依照價目表決定。\n",
                                        "行動\n從總督左邊開始，順時鐘方向，玩家抽2張牌選擇1張留著。\n\n特權\n總督可以抽5張牌並選擇1張留著。\n",
                                        "行動\n無。\n\n特權\n總督可以抽1張牌。\n"}};
const string cardDescription[2][30] = {{"\nproducer phase\nowner produces 1 indigo\n",
                                        "\nproducer phase\nowner produces 1 sugar\n",
                                        "\nproducer phase\nowner produces 1 tobacco\n",
                                        "\nproducer phase\nowner produces 1 coffee\n",
                                        "\nproducer phase\nowner produces 1 silver\n",
                                        "\nbeginning of a round\nwhen the governor checks players’ hands for the card limit of 7,\na player with a towerhasa hand limit of 12 instead of 7.\nOf course, if the owner of a tower has more than 12 cards at the\nbeginning of a round,he must discard all cards over 12 to the discard stack.\n",
                                        "\nbeginning of a round\nbefore the governor checks the players’ card limits(of 7 or 12),\nthe owner of a chapel may place any one of his hand cards\nface down under the chapel. At game end, the player scores 1 victory point for each card under his chapel.\n",
                                        "\nbuilder phase\nWhen the owner of a smithy builds a production building, he may pay one\ncard less to build it. When a player builds a violet building,\nhe gets no advantage from a smithy.\n",
                                        "\nbuilder phase\nAfter the owner of a poor house has built a building, he may draw 1 card\nfrom the card supply, adding it to his hand, if he has only 0\nor 1 card in his hand.\n",
                                        "\nbuilder phase\nWhen the owner of a black market builds any building,he may use up to 2 of\nhis goods(from his production buildings) instead of cards from\nhis hand, placing them face down on the discard stack just\nlike cards from his hand.\n",
                                        "\nbuilder phase\nThe owner of a crane may overbuild any of his existing buildings, placing the\nnew building card completely covering the old card. By doing\nso, he reduces the cost of the new building by the cost of\nthe old building.\n",
                                        "\nbuilder phase\nAfter the owner of a carpenter builds a violet building and paysthe buildingcost,\nhe may draw 1 card from the cardsupply and add it to his hand.\nThe carpenter has no special function when the player\nbuilds a production building.\n",
                                        "\nbuilder phase\nWhen the owner of a quarry builds a violet building, he pays 1 card less to build\nthe building.The quarry has no special function when the player\nbuilds a production building.\n",
                                        "\nproducer phase\nIn the producer phase, if the owner of a well produces at least 2 goods, he draws an additional card from\nthe cardsupply, adding it to hishand. It matters not whether he\nis the producer or not.\n",
                                        "\nproducer phase\nIn the producer phase, the owner of an aquaduct may produce 1 more good than otherwise possible\n",
                                        "\ntrader phase\nDuring the trader phase, if the owner of a market stand sells at least 2 goods,\nhe draws an additional card from the cardsupply, adding it to his hand.\nIt matters not whether he is the trader or not.\n",
                                        "\ntrader phase\nWhen the owner of a market hall sells at least one good,he draws 1 card more than\nthe price of the good sold from the card supply. If he sells more than 1 good,\nhe only draws one extra card, not 1 extra\ncard for each good sold.\n",
                                        "\ntrader phase\nDuring the trader phase, the owner of a trading post may sell 1 additional good from\nhis production buildings.\n",
                                        "\ncouncillor phase\nWhen any player selects the councillor role, the owner of an archive adds all cards\nhe draws to his hand and then chooses which cards to discard from his entire hand.\nIn other words,the player may discard drawn cards or cards he\nalready had in his hand instead of just drawn cards.\n",
                                        "\ncouncillor phase\nIn the councillor phase, the owner of a prefecture may keep 2 cards instead of 1\n",
                                        "\nprospector phase\nAfter a player selects the prospector role and takes the privilege (or not),\neach player who owns a gold mine, in clockwise order,may turn over\nthe top-most 4 cards from the card supply, placing them face up on the table:\n• if all four cards have different building costs,\nthe player adds any one of the cards to his hand and discards the other 3 cards face down on the discard stack.\n• if at least 2 of the cards have the same building cost, the player gets no card\nand discards all 4 cards face down onthe discard stack.\n",
                                        "\nall phases\nThe owner of a library may double the privilege of the role he selects.\n",
                                        "\nMomument\nNo special effect.\n",
                                        "\nMomument\nNo special effect.\n",
                                        "\nMomument\nNo special effect.\n",
                                        "\ngame end\nAt game end, the owner of a guild hall scores 2 victory points for each production building\nin his play area.\n",
                                        "\ngame end\nAt game end, the owner of a city hall scores 1 victory point for each violet building\nin his play area.\n",
                                        "\ngame end\nAt game end, the owner of a triumphal arch scores victory points(VP) for the monuments\nin hisplay area: for 1 monument he scores 4 VP, for 2 monument she scores 6 VP,\nand for 3 monuments he scores 8 VP.\n",
                                        "\ngame end\nAt game end, the owner of a palace scores an extra 1/4 of his victory points\n"},
                                        {"\nproducer phase\nowner produces 1 indigo\n",
                                        "\nproducer phase\nowner produces 1 sugar\n",
                                        "\nproducer phase\nowner produces 1 tobacco\n",
                                        "\nproducer phase\nowner produces 1 coffee\n",
                                        "\nproducer phase\nowner produces 1 silver\n",
                                        "\nbeginning of a round\nwhen the governor checks players’ hands for the card limit of 7,\na player with a towerhasa hand limit of 12 instead of 7.\nOf course, if the owner of a tower has more than 12 cards at the\nbeginning of a round,he must discard all cards over 12 to the discard stack.\n",
                                        "\nbeginning of a round\nbefore the governor checks the players’ card limits(of 7 or 12),\nthe owner of a chapel may place any one of his hand cards\nface down under the chapel. At game end, the player scores 1 victory point for each card under his chapel.\n",
                                        "\nbuilder phase\nWhen the owner of a smithy builds a production building, he may pay one\ncard less to build it. When a player builds a violet building,\nhe gets no advantage from a smithy.\n",
                                        "\nbuilder phase\nAfter the owner of a poor house has built a building, he may draw 1 card\nfrom the card supply, adding it to his hand, if he has only 0\nor 1 card in his hand.\n",
                                        "\nbuilder phase\nWhen the owner of a black market builds any building,he may use up to 2 of\nhis goods(from his production buildings) instead of cards from\nhis hand, placing them face down on the discard stack just\nlike cards from his hand.\n",
                                        "\nbuilder phase\nThe owner of a crane may overbuild any of his existing buildings, placing the\nnew building card completely covering the old card. By doing\nso, he reduces the cost of the new building by the cost of\nthe old building.\n",
                                        "\nbuilder phase\nAfter the owner of a carpenter builds a violet building and paysthe buildingcost,\nhe may draw 1 card from the cardsupply and add it to his hand.\nThe carpenter has no special function when the player\nbuilds a production building.\n",
                                        "\nbuilder phase\nWhen the owner of a quarry builds a violet building, he pays 1 card less to build\nthe building.The quarry has no special function when the player\nbuilds a production building.\n",
                                        "\nproducer phase\nIn the producer phase, if the owner of a well produces at least 2 goods, he draws an additional card from\nthe cardsupply, adding it to hishand. It matters not whether he\nis the producer or not.\n",
                                        "\nproducer phase\nIn the producer phase, the owner of an aquaduct may produce 1 more good than otherwise possible\n",
                                        "\ntrader phase\nDuring the trader phase, if the owner of a market stand sells at least 2 goods,\nhe draws an additional card from the cardsupply, adding it to his hand.\nIt matters not whether he is the trader or not.\n",
                                        "\ntrader phase\nWhen the owner of a market hall sells at least one good,he draws 1 card more than\nthe price of the good sold from the card supply. If he sells more than 1 good,\nhe only draws one extra card, not 1 extra\ncard for each good sold.\n",
                                        "\ntrader phase\nDuring the trader phase, the owner of a trading post may sell 1 additional good from\nhis production buildings.\n",
                                        "\ncouncillor phase\nWhen any player selects the councillor role, the owner of an archive adds all cards\nhe draws to his hand and then chooses which cards to discard from his entire hand.\nIn other words,the player may discard drawn cards or cards he\nalready had in his hand instead of just drawn cards.\n",
                                        "\ncouncillor phase\nIn the councillor phase, the owner of a prefecture may keep 2 cards instead of 1\n",
                                        "\nprospector phase\nAfter a player selects the prospector role and takes the privilege (or not),\neach player who owns a gold mine, in clockwise order,may turn over\nthe top-most 4 cards from the card supply, placing them face up on the table:\n• if all four cards have different building costs,\nthe player adds any one of the cards to his hand and discards the other 3 cards face down on the discard stack.\n• if at least 2 of the cards have the same building cost, the player gets no card\nand discards all 4 cards face down onthe discard stack.\n",
                                        "\nall phases\nThe owner of a library may double the privilege of the role he selects.\n",
                                        "\nMomument\nNo special effect.\n",
                                        "\nMomument\nNo special effect.\n",
                                        "\nMomument\nNo special effect.\n",
                                        "\ngame end\nAt game end, the owner of a guild hall scores 2 victory points for each production building\nin his play area.\n",
                                        "\ngame end\nAt game end, the owner of a city hall scores 1 victory point for each violet building\nin his play area.\n",
                                        "\ngame end\nAt game end, the owner of a triumphal arch scores victory points(VP) for the monuments\nin hisplay area: for 1 monument he scores 4 VP, for 2 monument she scores 6 VP,\nand for 3 monuments he scores 8 VP.\n",
                                        "\ngame end\nAt game end, the owner of a palace scores an extra 1/4 of his victory points\n"}};

/* 
Card List:
Indigo plant 染料廠, Sugar Mill 蔗糖廠, Tobacco storage 菸草廠, Coffee Roaster 咖啡廠, Silver smelter 白銀廠,
Tower 塔樓, Chapel 禮拜堂, Smithy 鐵匠鋪, Poor House 救濟院, Black Market 黑市,
Crane 起重機, Carpenter 木工場, Quarry 採石場, Well 水井, Aqueduct 溝渠,
Market Stand 攤販, Market Hall 市場, Trading Post 交易所, Archive 檔案館, Perfecture 辦公處, 
Gold mine 金礦坑, Library 圖書館, Statue 雕鑄像紀念碑, Victory Column 勝利柱紀念碑, Hero 英雄像紀念碑,
Guild Hall 同業會館, City Hall 市政廳, Triumhal Arch 凱旋門, Palace 宮殿
*/

const u8 initcardCounts[] = {10, 8, 8, 8, 8, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2};
const u8 vp[] = {1, 1, 2, 2, 3, 2, 2, 1, 1, 1, 1, 2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 3, 3, 4, 5, 0, 0, 0, 0};
const u8 type[] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2};
const u8 phase[] = {3, 3, 3, 3, 3, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 7, 8, 8, 8, 9, 9, 9, 9};
const u8 cost[] = {1, 2, 3, 4, 5, 3, 3, 1, 2, 2, 2, 3, 4, 2, 3, 2, 4, 2, 1, 3, 1, 5, 3, 4, 5, 6, 6, 6, 6};
const u8 priceList[5][5] = {{1, 1, 2, 2, 3},
                            {1, 2, 2, 2, 3},
                            {1, 1, 2, 2, 2},
                            {1, 2, 2, 3, 3},
                            {1, 1, 1, 2, 2}};

int cardCounts[29];
int language = 0;

player player_init = {
    .buildings = {-1},
    .deck = {-1},
    .builds = 0,
    .cards = 0,
    .maxcard = 6,
    .isbot = 1
};

player *p;

void printbanner(){ //print beautiful banner :)
        printf("=============================================\n");
        setcolor(YEL);
        printf(" ____                    _                    \n");
        printf("/ ___|  __ _ _ __       | |_   _  __ _ _ __  \n");
        printf("\\___ \\ / _` | '_ \\   _  | | | | |/ _` | '_ \\ \n");
        printf(" ___) | (_| | | | | | |_| | |_| | (_| | | | |\n");
        printf("|____/ \\__,_|_| |_|  \\___/ \\__,_|\\__,_|_| |_|\n");
        setcolor(RESET);
        printf("                            Made By 40947029S\n");
        printf("=============================================\n");
}

//Print Mainmenu
int mainmenu(){ 
    const string menutext[2] = {"(1)Start Game    (2)Set Language    (3)Exit", "(1)開始遊戲    (2)設定語言    (3)離開"};
    int rt = 0,invalid = 0;
    while(rt < 1 || rt > 3){
        CLEAR
        printbanner();
        printf("%s\n\n", menutext[language]);
        if(invalid) INVALID
        printf("Choice: ");
        scanf("%d", &rt);
        FLUSH
        if(rt < 1 || rt > 3){
            invalid = 1;
        }
    }
    return rt;
}

//Set Language
int setlanguage(){
    int rt = 0,invalid = 0;
    while(rt < 1 || rt > 2){
        CLEAR
        printbanner();
        printf("Set Language    設定語言\n");
        printf("(1) English    (2) 中文\n\n");
        if(invalid) INVALID
        printf("Choice: ");
        scanf("%d", &rt);
        FLUSH
        if(rt < 1 || rt > 2){
            invalid = 1;
        }
    }
    return rt-1;
}

//generate random card
int randomcard(int *cardCounts){ 
    int rt = rand() % 29;
    while(cardCounts[rt] == 0){
        rt = rand() % 29;
    }
    cardCounts[rt]--;
    return rt;
}

//game start init
void game_start(int players){ 
    int choice = 0, invalid = 0;
    p = calloc(4,sizeof(players));
    for(int i=0 ;i<29; i++){
        cardCounts[i] = initcardCounts[i];
    }
    cardCounts[0] -= players;
    for(int i=0; i<players; i++){
        p[i] = player_init;
        p[i].builds = 1;
        p[i].buildings[0] = 0;
        p[i].buildings[1] = -1;
        for(int j=0; j<4; j++){
            p[i].deck[j] = randomcard(cardCounts);
            p[i].cards++;
        }
    }
    p[0].isbot = 0;
    main_game(players);
}

//Main game
void main_game(int players){
    int gameover = 0;
    int governor = rand() % players;
    while(!gameover){
        int choserole[5] = {0,0,0,0,0};
        int playernow = governor;
        int count = players;
        while(count--){
            int role;
            if(p[playernow].isbot == 1){    //Select role bot action
                while(1){
                    role = rand() % 5;
                    if(choserole[role] == 0){
                        break;
                    }
                }
                CLEAR
                if(language == 0){
                    printf("Player %d chose %s\n",playernow+1, roleName[language][role]);
                }else{
                    printf("玩家 %d 選擇 %s\n",playernow+1, roleName[language][role]);
                }
                PAUSE
                CLEAR
            }else{      //Select role player action
                int invalid = 0;
                while(1){
                    CLEAR
                    if(language == 0){          
                        printf("Please Choose a role:\n ");
                    }else{
                        printf("請選擇職業:\n ");
                    }
                    for(int i=0; i<5; i++){
                        if(choserole[i] == 0){
                            printf("(%d) %s  ", i+1, roleName[language][i]);
                        }
                    }
                    printf("\n");
                    if(invalid) INVALID
                    printf("Choice: ");
                    scanf("%d", &role);
                    FLUSH
                    role--;
                    if(role < 0 || role > 4 || choserole[role] == 1){
                        invalid = 1;
                    }else{
                        break;
                    }
                }
            }
            choserole[role] = 1;

            //Call each role's function
            switch(role){
                case 0:
                    builder(playernow, players);
                    break;
                case 1:
                    //producer(playernow, players);
                    break;
                case 2:
                    //trader(playernow, players);
                    break;
                case 3:
                    //councilor(playernow, players);
                    break;
                case 4:
                    //prospector(playernow, players);
                    break;
            }
            playernow++;
            if(playernow == 4){
                playernow = 0;
            }
        }
        governor++;
        if(governor == 4){
            governor = 0;
        }
    }
}

//Print Player Hand Cards
void printdeck(int playernum){
    for(int i=0; i<p[playernum].cards; i++){
        printf("(%d) %s Cost:%u VP:%u\n", i+1, cardNameData[language][p[playernum].deck[i]], cost[p[playernum].deck[i]] , vp[p[playernum].deck[i]]);
    }
}

void rebuilddeck(int playernum){
    int tmp[12] = {-1},tmpcards = 0;
    for(int i=0; i<p[playernum].cards; i++){
        if(p[playernum].deck[i] != -1){
            tmp[tmpcards] = p[playernum].deck[i];
            tmpcards++;
        }
    }
    for(int i=0; i<12; i++){
        p[playernum].deck[i] = tmp[i];
    }
    p[playernum].cards = tmpcards;
}

void builder(int privilege, int players){
    //printf("Builder Phase\n");
    //PAUSE
    int playernow = privilege;
    int count = players;
    while(count--){
        if(p[playernow].isbot == 0){
            int choice, invalid = 0, costinvalid = 0;
            int costcount;
            int reducecost = 0;
            if(playernow == privilege){
                reducecost++;
            }
            while(1){   //Let user select card to build
                CLEAR
                printf("=============================\n");
                printdeck(playernow);
                printf("=============================\n");
                printf("(0)Skip Build (1-%d)Build\n\n", p[playernow].cards);
                if(invalid) INVALID
                if(costinvalid) printf("%sNot Enough Card to Pay The Cost%s\n",RED_BACK,RESET);
                printf("Choice:");
                scanf("%d", &choice);
                FLUSH
                if(choice < 0 || choice > p[playernow].cards){  //check for invalid input
                    invalid = 1;
                }else if(cost[p[playernow].deck[choice-1]]-reducecost > p[playernow].cards-1){
                    costinvalid = 1;
                }else{
                    costcount = cost[p[playernow].deck[choice-1]]-reducecost;
                    p[playernow].deck[choice-1] = -1;
                    rebuilddeck(playernow);
                    invalid = 0;
                    break;
                }
            }
            if(choice != 0){    //Discard cards to build
                int tmp = 1;
                while(tmp <= costcount){
                    while(1){
                        CLEAR
                        printf("=============================\n");
                        printdeck(playernow);
                        printf("=============================\n");
                        printf("Select A Card to Discard (%d/%d)\n", tmp, costcount);
                        if(invalid) INVALID
                        printf("Choice: ");
                        scanf("%d", &choice);
                        FLUSH
                        if(choice < 0 || choice > p[playernow].cards){
                            invalid = 1;
                        }else{
                            break;
                        }
                        p[playernow].deck[choice-1] = -1;
                        p[playernow].buildings[p[playernow].builds] = p[playernow].deck[choice-1];
                        p[playernow].builds++;
                        rebuilddeck(playernow);
                    }
                    tmp++;
                }
                p[playernow].deck[choice-1] = -1;
                p[playernow].buildings[p[playernow].builds] = p[playernow].deck[choice-1];
                p[playernow].builds++;
                rebuilddeck(playernow);
            }
        }else{
            int botbuild = rand() % 2;
            int built = 0;
            int reducecost = 0;
            int builtbuilding;
            int avaliable[p[playernow].cards];
            int avaliablenum = 0;
            if(playernow == privilege){
                reducecost++;
            }
            if(botbuild){
                for(int i=0; i<p[playernow].cards; i++){    //check which cards are buildable
                    if(cost[p[playernow].deck[i]]-reducecost <= p[playernow].cards-1){
                        avaliable[avaliablenum] = i;
                        avaliablenum++;
                    }
                }
                if(avaliablenum != 0){  //choose which card to build
                    int choice = rand() % avaliablenum;
                    choice = avaliable[choice];
                    int costcount = cost[p[playernow].deck[choice-1]]-reducecost;
                    builtbuilding = p[playernow].deck[choice];
                    p[playernow].deck[choice] = -1;
                    rebuilddeck(playernow);
                    if(costcount == p[playernow].cards){
                        for(int i=0 ;i<p[playernow].cards ;i++){
                            p[playernow].deck[i] = -1;
                        }
                        p[playernow].cards = 0;
                    }else{
                        while(costcount--){
                            while(1){
                                int discard = rand() % p[playernow].cards;
                                if(p[playernow].deck[discard] != -1){
                                    p[playernow].deck[discard] = -1;
                                    break;
                                }
                            }
                        }
                        built = 1;
                        rebuilddeck(playernow);
                    }
                }
            }
            CLEAR
            if(!built){
                if(language == 0){
                    printf("Player %d Skipped\n", playernow+1);
                }else{
                    printf("玩家 %d 跳過\n", playernow+1);
                }
            }else{
                if(language == 0){
                    printf("Player %d Built %s\n", playernow+1, cardNameData[language][builtbuilding]);
                }else{
                    printf("玩家 %d 建蓋 %s\n", playernow+1, cardNameData[language][builtbuilding]);
                }
            }
            PAUSE
        }
        playernow++;
        if(playernow == players){
            playernow = 0;
        }
    
    }
}