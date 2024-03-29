#include "sanjuan.h"

const string invalidtext[2] = {"Invalid Option", "錯誤選項"};
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
const string botactiontext[2] = {"Bot Action", "電腦回合"};
const string roleName[2][5] = {{"Builder", "Producer", "Trader", "Councilor", "Prospector"}, {"建築師", "生產者", "商人", "市長", "淘金者"}};

const string menutext[2] = {"(1)Start Game    (2)Set Language    (3)Exit", "(1)開始遊戲    (2)設定語言    (3)離開"};
const string printdecktext[2] = {"There is no card", "沒有手牌"};
const string buildertext[2][7] = {{"Skip Build", "Build", "Select A Card to Discard", "Not Enough Card to Pay The Cost", "You chose to build", "You skipped this round", "You can't build a duplicate non-production building"},
                                    "跳過", "建蓋", "選擇一張卡丟棄", "不夠支付該卡的花費", "你選擇建蓋", "你跳過了此回合", "你無法建造重複的非生產建築"};
const string producertext[2][6] = {{"Skip Produce", "Produce", "You are unable to produce any goods", "Choose one production building to produce", "produced 1 good", "You skipped this produce phase"},
                                    "跳過", "生產", "你無法進行任何生產", "選擇任一生產建築進行生產", "產出一份資源", "你跳過了此次生產"};
const string tradertext[2][5] = {{"You don't have any goods to sell","Choose one good to sell","Skip","Sell Good","You skipped this round"},
                                    {"你沒有任何資源可供售出","選擇一項資源售出","跳過","賣出資源", "你跳過此回合"}};
const string councilortext[2][1] = {{"Choose a card to keep"},
                                        {"選擇保留其中一張卡"}};

/* 
Card List:
Indigo plant 染料廠, Sugar Mill 蔗糖廠, Tobacco storage 菸草廠, Coffee Roaster 咖啡廠, Silver smelter 白銀廠,
Tower 塔樓(✔), Chapel 禮拜堂(✔), Smithy 鐵匠鋪(✔), Poor House 救濟院(✔), Black Market 黑市(✔, lazy),
Crane 起重機(✔, no bot), Carpenter 木工場(✔), Quarry 採石場(✔), Well 水井(✔), Aqueduct 溝渠(✔),
Market Stand 攤販(✔), Market Hall 市場(✔),, Trading Post 交易所(✔), Archive 檔案館(✔, no bot), Perfecture 辦公處(✔), 
Gold mine 金礦坑(✔), Library 圖書館(✔), Statue 雕鑄像紀念碑, Victory Column 勝利柱紀念碑, Hero 英雄像紀念碑,
Guild Hall 同業會館(✔), City Hall 市政廳(✔), Triumhal Arch 凱旋門(✔), Palace 宮殿(✔)
*/

const u8 initcardCounts[] = {10, 8, 8, 8, 8, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2};
const u8 vp[] = {1, 1, 2, 2, 3, 2, 2, 1, 1, 1, 1, 2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 3, 3, 4, 5, 0, 0, 0, 0};
const u8 type[] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1};
const u8 phase[] = {3, 3, 3, 3, 3, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 7, 8, 8, 8, 9, 9, 9, 9};
const u8 cost[] = {1, 2, 3, 4, 5, 3, 3, 1, 2, 2, 2, 3, 4, 2, 3, 2, 4, 2, 1, 3, 1, 5, 3, 4, 5, 6, 6, 6, 6};
const u8 priceList[5][5] = {{1, 1, 2, 2, 3},
                            {1, 2, 2, 2, 3},
                            {1, 1, 2, 2, 2},
                            {1, 2, 2, 3, 3},
                            {1, 1, 1, 2, 2}};

int cardCounts[29] = {0};
int discardcard[29] = {0};
int totalcard = 110;
int language = 0;
int gameover = 0;
int players = 4;

const player player_init = {
    .buildings = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    .hasgoods = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    .deck = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    .builds = 0,
    .cards = 0,
    .maxcard = 7,
    .isbot = 1,
    .chapelvp = 0
};

player *p;

//print beautiful banner :)
void printbanner(){ 
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

//check gameover
void isgameover(){
    for(int i=0; i<players; i++){
        if(p[i].builds == 12){
            gameover = 1;
        }
    }
}

//Set Language
void setlanguage(){
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
    language = rt-1;
}

void setplayers(){
    int rt = 0,invalid = 0;
    while(rt < 2 || rt > 3){
        CLEAR
        if(language == 0){
            printf("How many bot do you want to play with? (2-3)\n");
        }else{
            printf("需要加入多少電腦? (2-3)\n");
        }
        if(invalid) INVALID
        printf("Choice: ");
        scanf("%d", &rt);
        FLUSH
        if(rt < 2 || rt > 3){
            invalid = 1;
        }
    }
    players = rt+1;
}

//generate random card
int randomcard(){ 
    if(totalcard == 0){
        for(int i=0; i<29; i++){
            cardCounts[i] = discardcard[i];
            discardcard[i] = 0;
        }
    }
    int rt = rand() % 29;
    while(cardCounts[rt] == 0){
        rt = rand() % 29;
    }
    totalcard--;
    cardCounts[rt]--;
    return rt;
}

//game start init
void game_start(){ 
    setplayers();
    int choice = 0, invalid = 0;
    p = calloc(players,sizeof(player));
    for(int i=0 ;i<29; i++){
        cardCounts[i] = initcardCounts[i];
    }
    cardCounts[0] -= players;
    totalcard -= players;
    for(int i=0; i<players; i++){
        p[i] = player_init;
        p[i].builds = 1;
        p[i].buildings[0] = 0;
        
        for(int j=0; j<4; j++){
            p[i].deck[j] = randomcard(cardCounts);
            p[i].cards++;
        }
        printf("%d\n", p[i].hasgoods[1]);
    }
    p[0].isbot = 0;
    main_game(players);
}

//Main game
void main_game(){
    int governor = rand() % players;
    while(!gameover){
        int choserole[5] = {0};
        int playernow = governor;
        int count = players;
        for(int i=0; i<players; i++){
            chapels(i);
            cardoverflow(i);
        }
        while(count--){
            if(gameover){
                break;
            }
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
                checkstat(playernow);
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
                    builder(playernow);
                    break;
                case 1:
                    producer(playernow);
                    break;
                case 2:
                    trader(playernow);
                    break;
                case 3:
                    councilor(playernow);
                    break;
                case 4:
                    prospector(playernow);
                    break;
            }
            CLEAR
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
    int maxvp = 0, winner;
    int vps[players];
    for(int i=0; i<players; i++){
        vps[i] = 0;
    }
    caculatevp(vps, 1);
    for(int i=0; i<players; i++){
        if(vps[i] > maxvp){
            winner = i+1;
            maxvp = vp[i];
        }
    }
    setcolor(RED_BACK)
    if(language == 0){
        printf("Player %d is the winner !!!", winner);
    }else{
        printf("玩家 %d 贏了 !!!", winner);
    }
    setcolor(RESET)
    free(p);
}

int checkbuilding(int playernum, int cardnum){
    int rt = 0;
    for(int i=0; i<p[playernum].builds; i++){
        if(p[playernum].buildings[i] == cardnum){
            rt = 1;
            break;
        }
    }
    return rt;
}

//print all player stats
void checkstat(int playernow){
    CLEAR
    int vps[players];
    for(int i=0; i<players; i++){
        vps[i] = 0;
    }
    caculatevp(vps, 0);
    for(int i=0; i<players; i++){
        printf("=============================\n");
        if(language == 0){
            printf("Player %d VP: %d\n", i+1, vps[i]);
        }else{
            printf("玩家 %d VP: %d\n", i+1, vps[i]);
        }
        for(int j=0; j<p[i].builds; j++){
            printf("(%d) %s ", j+1, cardNameData[language][p[i].buildings[j]]);
            if(p[i].hasgoods[j] != -1){
                if(language == 0){
                    setcolor(GRN_BACK);
                    printf("(Has good)");
                    setcolor(RESET);
                }else{
                    setcolor(GRN_BACK);
                    printf("(有資源)");
                    setcolor(RESET);
                }
            }
            if(p[i].buildings[j] == 6 && p[i].chapelvp){
                setcolor(MAG_BACK);
                printf("(%d cards under)", p[i].chapelvp);
                setcolor(RESET);
            }
            printf("\n");
        }
    }
    printf("=============================\n");
    if(language == 0){
        printf("Your hand:\n");
    }else{
        printf("你的手牌:\n");
    }
    for(int i=0; i<p[playernow].cards; i++){
        printf("(%d) %s\n", i+1, cardNameData[language][p[playernow].deck[i]]);
    }
    printf("=============================\n");
    PAUSE
}

//Print player's hand
void printdeck(int playernum){
    for(int i=0; i<p[playernum].cards; i++){
        printf("(%d) %s Cost:%u VP:%u\n", i+1, cardNameData[language][p[playernum].deck[i]], cost[p[playernum].deck[i]] , vp[p[playernum].deck[i]]);
    }
    if(p[playernum].cards == 0){
        setcolor(RED_BACK);
        printf("%s\n", printdecktext[language]);
        setcolor(RESET);
    }
}

//print player's buildings
void printbuilding(int playernum){
    for(int i=0; i<p[playernum].builds; i++){
        printf("(%d) %s goods:%d\n", i+1, cardNameData[language][p[playernum].buildings[i]], p[playernum].hasgoods[i]);
    }
}

//rebuild player's hand
void rebuilddeck(int playernum){
    //printf("Rebuilding...");
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
    //printf("Success\n");
}

//discard card from player's hand
void playerdiscard(int playernum, int cardpos){
    discardcard[p[playernum].deck[cardpos]]++;
    p[playernum].deck[cardpos] = -1;
    rebuilddeck(playernum);
}

void caculatevp(int *vps, int verbose){
    //Guild Hall 同業會館 (25), City Hall 市政廳 (26), Triumhal Arch 凱旋門 (27), Palace 宮殿 (28)
    for(int i=0; i<players; i++){
        int bonus;
        for(int j=0; j<p[i].builds; j++){
            vps[i] += vp[p[i].buildings[j]];
        }
        if(verbose){
            printf("Player %d", i+1);
            printf("=============================\n");
            setcolor(GRN)
            printf("Original VPs: %d", vps[i]);
            setcolor(RESET)
        }
        if(p[i].chapelvp){
            if(verbose){
                setcolor(GRN_BACK)
                printf("Chapel + %d VPs", p[i].chapelvp);
                setcolor(RESET)
            }
            vps[i] += p[i].chapelvp;
        }
        bonus = guildhall(i);
        if(bonus){
            if(verbose){
                if(language == 0){
                    printf("Use %sguild hall's%s ability, get 2 additional vp for every production building you build.\n", GRN, RESET);
                }else{
                    printf("發動 %s同業會館%s 能力, 每擁有一棟生產建築物可額外獲得2分\n", GRN, RESET);
                }
                setcolor(GRN_BACK)
                printf("+ %d VPs", bonus);
                setcolor(RESET)
            }
            vps[i] += bonus;
        }
        bonus = cityhall(i);
        if(bonus){
            if(verbose){
                if(language == 0){
                    printf("Use %scity hall's%s ability, get 1 additional vp for every non-production building you build.\n", GRN, RESET);
                }else{
                    printf("發動 %s市政廳%s 能力, 每擁有一棟非生產建築物可額外獲得1分\n", GRN, RESET);
                }
                setcolor(GRN_BACK)
                printf("+ %d VPs\n", bonus);
                setcolor(RESET)
            }

            vps[i] += bonus;
        }
        bonus = triumhalarch(i);
        if(bonus){
            if(verbose){
                if(language == 0){
                    printf("Use %striumhal arch's%s ability, get 4 additional vp for one monument.\n", GRN, RESET);
                    printf("                                 6 additional vp for two monuments.\n");
                    printf("                                 8 additional vp for three monuments.\n");
                }else{
                    printf("發動 %s凱旋門%s 能力, 擁有一棟紀念碑可額外獲得4分\n", GRN, RESET);
                    printf("                     兩棟紀念碑可額外獲得6分\n");
                    printf("                     三棟紀念碑可額外獲得8分\n");
                }
                setcolor(GRN_BACK)
                printf("+ %d VPs\n", bonus);
                setcolor(RESET)
            }

            vps[i] += bonus;
        }
        bonus = palace(i, vps[i]);
        if(bonus){
            if(verbose){
                if(language == 0){
                    printf("Use %spalace's%s ability, get 1 additional vp for every 4 victory points.\n", GRN, RESET);
                }else{
                    printf("發動 %s宮殿%s 能力, 每獲得四分可額外獲得1分\n", GRN, RESET);
                }
                setcolor(GRN_BACK)
                printf("+ %d VPs\n", bonus);
                setcolor(RESET)
            }
            vps[i] += bonus;
        }
        if(verbose){
            setcolor(MAG_BACK)
            printf("Total VPs: %d\n", vp[i]);
            setcolor(RESET)
            printf("=============================\n");
        }
    }
}

void cardoverflow(int playernow){
    const string cardoftext[2][1] = {{"Choose one card to discard"},
                                     {"選擇一張卡丟棄"}};
    if(p[playernow].cards > p[playernow].maxcard){
        if(p[playernow].isbot == 0){
            int choice, invalid;
            while(p[playernow].cards > p[playernow].maxcard){
                CLEAR
                if(language == 0){
                    printf("You exceeded max card limit (%d)\n Number of hands: %d\n", p[playernow].maxcard, p[playernow].cards);
                }else{
                    printf("你超過了手牌上限 (%d)\n 手牌數量: %d\n", p[playernow].maxcard, p[playernow].cards);
                }
                printf("=============================\n");
                printdeck(playernow);
                printf("=============================\n");
                printf("%s\n", cardoftext[language][0]);
                if(invalid) INVALID
                printf("Choice: ");
                scanf("%d", &choice);
                FLUSH
                if(choice < 1 || choice > p[playernow].cards){
                    invalid = 1;
                }else{
                    choice--;
                    playerdiscard(playernow, choice);
                    
                }
            }
        }else{
            CLEAR
            if(language == 0){
                printf("Player %d exceeded max card limit (%d) and discarded %d card(s)\n", playernow+1, p[playernow].maxcard, p[playernow].cards - p[playernow].maxcard);
            }else{
                printf("玩家 %d 超過了手牌上限 (%d) 並丟棄了 %d 張手牌\n", playernow+1, p[playernow].maxcard, p[playernow].cards - p[playernow].maxcard);
            }
            while(p[playernow].cards > p[playernow].maxcard){
                int choice = rand() % p[playernow].cards;
                playerdiscard(playernow, choice);
            }
            PAUSE
        }
    }
}

//builderphase
void builder(int privilege){
    //printf("Builder Phase\n");
    //PAUSE
    int playernow = privilege;
    int count = players;
    while(count--){
        if(p[playernow].isbot == 0){
            int choice, invalid = 0, costinvalid = 0, duplicate= 0;
            int costcount;
            int reducecost = 0;
            int tmpbuilding = -1;
            if(playernow == privilege){
                reducecost++;
            }
            reducecost += library(playernow, 1);
            while(1){   //Let user select card to build
                CLEAR
                printf("=============================\n");
                printdeck(playernow);
                printf("=============================\n");
                printf("(0)%s ", buildertext[language][0]);
                if(p[playernow].cards > 0){
                    printf("(1-%d)%s", p[playernow].cards, buildertext[language][1]);
                }
                printf("\n\n");
                if(invalid) INVALID
                if(costinvalid) printf("%s%s%s\n",RED_BACK, buildertext[language][3],RESET);
                if(duplicate) printf("%s%s%s\n",RED_BACK, buildertext[language][6],RESET);
                printf("Choice:");
                scanf("%d", &choice);
                FLUSH
                invalid = 0;
                costinvalid = 0;
                duplicate = 0;
                if(choice < 0 || choice > p[playernow].cards){  //check for invalid input
                    invalid = 1;
                }else if(choice != 0 && cost[p[playernow].deck[choice-1]]-reducecost > p[playernow].cards-1){
                    costinvalid = 1;
                }else if(choice != 0 && type[p[playernow].deck[choice-1]] != 0 && checkbuilding(playernow, p[playernow].deck[choice-1])){
                    duplicate = 1;
                }else if(choice != 0){
                    tmpbuilding = p[playernow].deck[choice-1];
                    int iscrane = crane(playernow);
                    if(iscrane > -1){
                        discardcard[p[playernow].buildings[iscrane]]++;
                        if(p[playernow].hasgoods[iscrane] > -1){
                            discardcard[p[playernow].hasgoods[iscrane]]++;
                            p[playernow].hasgoods[iscrane] = -1;
                        }
                        costcount = cost[tmpbuilding] - cost[p[playernow].buildings[iscrane]];
                        p[playernow].buildings[iscrane] = tmpbuilding;
                        p[playernow].deck[choice-1] = -1;
                        rebuilddeck(playernow);
                        invalid = 0;
                    }else{
                        reducecost += smithy(playernow, tmpbuilding) + quarry(playernow, tmpbuilding);
                        costcount = cost[p[playernow].deck[choice-1]]-reducecost;
                        p[playernow].buildings[p[playernow].builds] = p[playernow].deck[choice-1];
                        p[playernow].builds++;
                        reducecost += blackmarket(playernow, costcount);
                        costcount = cost[p[playernow].deck[choice-1]]-reducecost;
                        isgameover();
                        p[playernow].deck[choice-1] = -1;
                        rebuilddeck(playernow);
                        invalid = 0;
                    }

                    break;
                }else{
                    break;
                }
            }
            if(choice != 0){    //Discard cards to build
                printf("\n=============================\n");
                printf("%s %s\n", buildertext[language][4], cardNameData[language][tmpbuilding]);
                PAUSE
                int tmp = 1;
                while(tmp <= costcount){
                    while(1){
                        CLEAR
                        printf("=============================\n");
                        printdeck(playernow);
                        printf("=============================\n");
                        printf("%s (%d/%d)\n", buildertext[language][2], tmp, costcount);
                        if(invalid) INVALID
                        printf("Choice: ");
                        scanf("%d", &choice);
                        FLUSH
                        if(choice < 0 || choice > p[playernow].cards){
                            invalid = 1;
                        }else{
                            break;
                        }
                    }
                    playerdiscard(playernow, choice-1);
                    tmp++;
                }
                poorhouse(playernow);
                tower(playernow, tmpbuilding);
                carpenter(playernow, tmpbuilding);
            }else{
                printf("\n=============================\n");
                printf("%s\n", buildertext[language][5]);
                PAUSE
            }
        }else{
            CLEAR
            setcolor(CYN);
            printf("%s\n", botactiontext[language]);
            setcolor(RESET);
            printf("=============================\n");
            int botbuild = rand() % 2;
            int built = 0;
            int reducecost = 0;
            int builtbuilding;
            int avaliable[p[playernow].cards];
            int avaliablenum = 0;
            if(playernow == privilege){
                reducecost++;
            }
            reducecost += library(playernow, 1);
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
                    builtbuilding = p[playernow].deck[choice];
                    reducecost += smithy(playernow, builtbuilding) + quarry(playernow, builtbuilding);
                    int costcount = cost[p[playernow].deck[choice]]-reducecost;
                    p[playernow].buildings[p[playernow].builds] = builtbuilding;
                    p[playernow].builds++;
                    isgameover();
                    p[playernow].deck[choice] = -1;
                    rebuilddeck(playernow);
                    if(costcount == p[playernow].cards){
                        for(int i=0 ;i<p[playernow].cards ;i++){
                            p[playernow].deck[i] = -1;
                        }
                        p[playernow].cards = 0;
                        built = 1;
                    }else{
                        while(costcount--){
                            while(1){
                                int discard = rand() % p[playernow].cards;
                                if(p[playernow].deck[discard] != -1){
                                    p[playernow].deck[discard] = -1;
                                    playerdiscard(playernow, discard);
                                    break;
                                }
                            }
                        }
                        built = 1;
                        poorhouse(playernow);
                        tower(playernow, builtbuilding);
                        carpenter(playernow, builtbuilding);
                    }
                }
            }
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

//producer phase
void producer(int privilege){
    int playernow = privilege;
    int count = players;

    while(count--){
        int producecount = 1;
        int produceable = 0;
        int producebuilding[12] = {-1};
        int produced = 0;
        if(playernow == privilege){
            producecount++;
        }
        producecount += aqueduct(playernow);
        int haslibrary = library(playernow, 2);
        if(haslibrary){
            producecount = haslibrary;
        }
        if(p[playernow].isbot == 0){
            for(int i=0; i<p[playernow].builds; i++){
                if(type[p[playernow].buildings[i]] == 0 && p[playernow].hasgoods[i] == -1){
                    producebuilding[produceable] = i;
                    produceable++;
                }
            }
            if(produceable < producecount){
                producecount = produceable;
            }
            int tmptotal = producecount, tmpcount = 1;
            if(produceable){
                
                while(producecount--){
                    int choice = -1, invalid = 0;
                    //User enter produce choice
                    while(1){   
                        CLEAR
                        printf("=============================\n");
                        for(int i=0; i<produceable; i++){
                            printf("(%d) %s\n", i+1, cardNameData[language][p[playernow].buildings[producebuilding[i]]]);
                        }
                        printf("=============================\n");
                        printf("%s (%d/%d)\n", producertext[language][3], tmpcount, tmptotal);
                        printf("(0)%s (1-%d)%s\n\n", producertext[language][0], produceable, producertext[language][1]);
                        if(invalid) INVALID
                        printf("Choice: ");
                        scanf("%d", &choice);
                        FLUSH
                        if(choice < 0 || choice > produceable){
                            invalid = 1;
                        }else{
                            break;
                        }
                    }
                    //produce: get randomcard or skip
                    if(choice){
                        //get supply
                        produced++;
                        choice--;
                        p[playernow].hasgoods[producebuilding[choice]] = randomcard();
                        discardcard[p[playernow].hasgoods[producebuilding[choice]]]++;
                        produceable = 0;
                        printf("\n=============================\n");
                        printf("%s %s\n", cardNameData[language][p[playernow].buildings[producebuilding[choice]]], producertext[language][4]);
                        PAUSE
                        for(int i=0 ; i<12; i++){
                            producebuilding[i] = -1;
                        }
                        for(int i=0; i<p[playernow].builds; i++){
                            if(type[p[playernow].buildings[i]] == 0 && p[playernow].hasgoods[i] == -1){
                                producebuilding[produceable] = i;
                                produceable++;
                            }
                        }
                    }else{
                        //skipped produce
                        printf("\n=============================\n");
                        printf("%s\n", producertext[language][5]);
                    }

                    tmpcount++;
                }
            }else{
                CLEAR
                setcolor(RED_BACK);
                printf("%s\n", producertext[language][2]);
                setcolor(RESET);
                PAUSE
            }
        }else{
            CLEAR
            setcolor(CYN);
            printf("%s\n", botactiontext[language]);
            setcolor(RESET);
            printf("=============================\n");
            int isproduce = rand() % 2;
            for(int i=0; i<p[playernow].builds; i++){
                if(type[p[playernow].buildings[i]] == 0 && p[playernow].hasgoods[i] == -1){
                    producebuilding[produceable] = i;
                    produceable++;
                }
            }
            if(produceable < producecount){
                producecount = produceable;
            }
            if(isproduce && produceable){
                while(producecount--){
                    int choice = rand() % produceable;
                    p[playernow].hasgoods[producebuilding[choice]] = randomcard();
                    int tmpbuilding = producebuilding[choice];
                    produceable = 0;
                    produced++;
                    if(language == 0){
                        printf("Player %d's %s %s\n", playernow+1, cardNameData[language][p[playernow].buildings[tmpbuilding]], producertext[language][4]);
                    }else{
                        printf("玩家 %d 的 %s %s\n", playernow+1, cardNameData[language][p[playernow].buildings[tmpbuilding]], producertext[language][4]);
                    }
                    PAUSE
                    for(int i=0 ; i<12; i++){
                        producebuilding[i] = -1;
                    }
                    for(int i=0; i<p[playernow].builds; i++){
                        if(type[p[playernow].buildings[i]] == 0 && p[playernow].hasgoods[i] == -1){
                            producebuilding[produceable] = i;
                            produceable++;
                        }
                    }
                }
            }else{
                if(language == 0){
                    printf("Player %d skipped this round\n", playernow+1);
                }else{
                    printf("玩家 %d 跳過了此次生產\n", playernow+1);
                }
                PAUSE
            }
            
        }
        well(playernow, produced);
        playernow++;
        if(playernow == players){
            playernow = 0;
        }
        
    }
}

//trader phase
void trader(int privilege){
    int playernow = privilege;
    int count = players;
    int pricecard = rand() % 5;
    while(count--){
        int tradecount = 1;
        int sellcount = 0;
        int goods[12] = {-1},sellable = 0;
        CLEAR
        printf("=============================\n\n");
        printf("        Price List :           \n");
        printf("        %s%d %s%d %s%d %s%d %s%d \n\n", MAG_BACK, priceList[pricecard][0],YEL_BACK, priceList[pricecard][1],GRN_BACK, priceList[pricecard][2],BLU_BACK, priceList[pricecard][3],CYN_BACK, priceList[pricecard][4]);
        setcolor(RESET);
        printf("=============================\n");        
        if(p[playernow].isbot == 0){    //User Action
            if(playernow == privilege){
                tradecount++;
            }
            tradecount += tradingpost(playernow);
            int haslibrary = library(playernow, 3);
            if(haslibrary){
                    tradecount = haslibrary;
            }
            //check if player has card to sell
            for(int i=0; i<p[playernow].builds; i++){
                if(p[playernow].hasgoods[i] != -1){
                    goods[sellable] = i;
                    sellable++;
                }
            }
            if(sellable < tradecount){
                tradecount = sellable;
            }
            if(sellable){
                int choice, invalid = 0;
                const int consttradecount = tradecount;
                while(tradecount){
                    for(int i=0; i<sellable; i++){
                        printf("(%d) %s\n", i+1, cardNameData[language][p[playernow].buildings[goods[i]]]);
                    }
                    printf("=============================\n");
                    printf("%s (%d/%d)\n", tradertext[language][1], consttradecount - tradecount + 1, consttradecount);
                    printf("(0) %s (1-%d) %s\n", tradertext[language][2], sellable, tradertext[language][3]);
                    printf("Choice: ");
                    scanf("%d", &choice);
                    FLUSH
                    if(choice < 0 || choice > sellable){
                        invalid = 1;
                        continue;
                    }else if(choice){
                        choice--;
                        sellcount++;
                        int producebuilding = p[playernow].buildings[goods[choice]];
                        p[playernow].hasgoods[goods[choice]] = -1;  //sell good
                        //Get supply
                        for(int i=0; i<priceList[pricecard][producebuilding]; i++){
                            p[playernow].deck[p[playernow].cards] = randomcard();
                            p[playernow].cards++;
                        }
                        if(language == 0){
                            printf("\n=============================\n");
                            printf("You sold good from %s and get %d ", cardNameData[language][producebuilding], priceList[pricecard][producebuilding]);
                            if(priceList[pricecard][producebuilding] == 1){
                                printf("supply\n");
                            }else{
                                printf("supplies\n");
                            }
                        }else{
                            printf("\n=============================\n");
                            printf("你在 %s 賣出了一份資源並且得到 %d 張手牌\n", cardNameData[language][producebuilding], priceList[pricecard][producebuilding]);
                        }
                        PAUSE
                        tradecount--;
                    }else{
                        printf("\n=============================\n");
                        printf("%s\n", tradertext[language][4]);
                        tradecount--;
                        PAUSE
                    }
                }

            }else{
                setcolor(RED_BACK);
                printf("%s\n", tradertext[language][0]);
                setcolor(RESET);
                PAUSE
            }
            marketstand(playernow, sellcount);
            if(sellcount){
                markethall(playernow);
            }
        }else{                         //Bot action
            int botaction = rand() % 2;
            setcolor(CYN);
            printf("%s\n", botactiontext[language]);
            setcolor(RESET);
            printf("=============================\n");
            if(botaction){
                int sellcount = 0;
                if(playernow == privilege){
                    tradecount++;
                }
                int haslibrary = library(playernow, 3);
                if(haslibrary){
                    tradecount = haslibrary;
                }
                tradecount += tradingpost(playernow);
                for(int i=0; i<p[playernow].builds; i++){
                    if(p[playernow].hasgoods[i] != -1){
                        goods[sellable] = i;
                        sellable++;
                    }
                }
                if(sellable < tradecount){
                    tradecount = sellable;
                }
                if(tradecount){
                    while(tradecount){
                        int choice = rand() % sellable;
                        int producebuilding = p[playernow].buildings[goods[choice]];
                        p[playernow].hasgoods[goods[choice]] = -1;  //sell good
                        //Get supply
                        for(int i=0; i<priceList[pricecard][producebuilding]; i++){
                            p[playernow].deck[p[playernow].cards] = randomcard();
                            p[playernow].cards++;
                        }
                        if(language == 0){
                            printf("Player %d sold good from %s and get %d ", playernow+1, cardNameData[language][producebuilding], priceList[pricecard][producebuilding]);
                            if(priceList[pricecard][producebuilding] == 1){
                                printf("supply\n");
                            }else{
                                printf("supplies\n");
                            }
                        }else{
                            printf("玩家 %d 在 %s 賣出了一份資源並且得到 %d 張手牌\n", playernow+1, cardNameData[language][producebuilding], priceList[pricecard][producebuilding]);
                        }
                        sellcount++;
                        tradecount--;
                        PAUSE
                    }
                }else{
                    if(language == 0){
                        printf("Player %d skipped this round\n", playernow+1);
                    }else{
                        printf("玩家 %d 跳過了此回合\n", playernow+1);
                    }
                    PAUSE 
                }
                marketstand(playernow, sellcount);
                markethall(playernow);
            }else{
                if(language == 0){
                    printf("Player %d skipped this round\n", playernow+1);
                }else{
                    printf("玩家 %d 跳過了此回合\n", playernow+1);
                }
                PAUSE
            }
            
        }
        playernow++;
        if(playernow == players){
            playernow = 0;
        }
    }
}

//councilor phase
void councilor(int privilege){
    int playernow = privilege;
    int count = players;
    while(count--){
        int tmpcards[8] = {-1};
        int getcard = 2;
        int keepcard = 1;
        if(p[playernow].isbot == 0){
            if(playernow == privilege){
                getcard = 5;
            }
            int haslibrary = library(playernow, 4);
            if(haslibrary){
                getcard = haslibrary;
            }
            keepcard += prefecture(playernow);
            for(int i=0; i<getcard; i++){
                tmpcards[i] = randomcard(); 
            }
            if(archive(playernow, tmpcards, getcard, keepcard)){
                playernow++;
                if(playernow == players){
                    playernow = 0;
                }
                continue;
            }
            int keepcardcount = keepcard;
            int choice = 0, invalid = 0;
            while(keepcardcount){
                CLEAR
                printf("=============================\n"); 
                for(int i=0; i<getcard; i++){
                    printf("(%d) %s Cost:%u VP:%u\n", i+1, cardNameData[language][tmpcards[i]], cost[tmpcards[i]] , vp[tmpcards[i]]);
                }
                printf("=============================\n"); 
                printf("%s (%d/%d)\n", councilortext[language][0], keepcard - keepcardcount+1, keepcard);
                if(invalid) INVALID;
                printf("Choice: ");
                scanf("%d", &choice);
                FLUSH
                if(choice < 1 || choice > getcard){
                    invalid = 1;
                }else{
                    choice--;
                    p[playernow].deck[p[playernow].cards] = tmpcards[choice];
                    p[playernow].cards++;
                    keepcardcount--;
                    if(language == 0){
                        printf("\n=============================\n"); 
                        printf("You Chose %s to keep\n",cardNameData[language][tmpcards[choice]]);
                        PAUSE
                    }else{
                        printf("\n=============================\n"); 
                        printf("你選擇保留 %s\n",cardNameData[language][tmpcards[choice]]);
                        PAUSE
                    }
                    int tmparr[getcard-1];
                    int tmpcount = 0;
                    tmpcards[choice] = -1;
                    for(int i=0; i<getcard; i++){
                        if(tmpcards[i] != -1){
                            tmparr[tmpcount] = tmpcards[i];
                            tmpcount++;
                        }
                    }
                    getcard--;
                    for(int i=0; i<getcard; i++){
                        tmpcards[i] = tmparr[i];
                    }
                }
                for(int i=0; i<getcard; i++){
                    discardcard[tmpcards[i]]++;
                }
            }
        }else{
            if(playernow == privilege){
                getcard = 5;
            }
            int haslibrary = library(playernow, 4);
            if(haslibrary){
                getcard = haslibrary;
            }
            for(int i=0; i<getcard; i++){
                tmpcards[i] = randomcard(); 
            }
            keepcard += prefecture(playernow);
            CLEAR
            setcolor(CYN);
            printf("%s\n", botactiontext[language]);
            setcolor(RESET);
            printf("=============================\n");
            if(language == 0){
                printf("Player %d got %d cards\n", playernow+1, keepcard);
            }else{
                printf("玩家 %d 保留了 %d 張卡\n", playernow+1, keepcard);
            }
            while(keepcard--){
                int choice = rand() % getcard;
                while(tmpcards[choice] == -1){
                    choice = rand() % getcard;
                }
                p[playernow].deck[p[playernow].cards] = tmpcards[choice];
                discardcard[tmpcards[choice]]++;
                p[playernow].cards++;
                tmpcards[choice] = -1;
            }
            int tmparr[getcard-1];
            int tmpcount = 0;
            for(int i=0; i<getcard; i++){
                if(tmpcards[i] != -1){
                    tmparr[tmpcount] = tmpcards[i];
                    tmpcount++;
                }
            }
            getcard = tmpcount;
            for(int i=0; i<getcard; i++){
                discardcard[tmpcards[i]]++;
            }
            PAUSE
        }
        playernow++;
        if(playernow == players){
            playernow = 0;
        }
    }
}

void prospector(int privilege){
    int playernow = privilege;
    int getcardnum = 1;
    int count = players;
    while(count--){
        if(playernow == privilege){
            CLEAR
            getcardnum += library(playernow, 5);
            while(getcardnum--){
                int getcard = randomcard();
                p[playernow].deck[p[playernow].cards] = getcard;
                p[playernow].cards++;
                
                if(p[playernow].isbot == 0){
                    if(language == 0){
                        printf("Player %d got %s\n", playernow+1, cardNameData[language][getcard]);
                    }else{
                        printf("玩家 %d 拿到了 %s\n", playernow+1, cardNameData[language][getcard]);
                    }
                }else{
                    setcolor(CYN);
                    printf("%s\n", botactiontext[language]);
                    setcolor(RESET);
                    printf("=============================\n");
                    if(language == 0){
                        printf("Player %d got one card\n", playernow+1);
                    }else{
                        printf("玩家 %d 拿到了一張卡\n", playernow+1);
                    }
                }
                PAUSE
            }

        }
        goldmine(playernow);
        playernow++;
        if(playernow == players){
            playernow = 0;
        }
    }
}

int smithy(int playernow, int builtbuilding){
    //Smithy 鐵匠鋪 (7)
    int rt = 0;
    if(type[builtbuilding] == 0 && checkbuilding(playernow, 7)){
        if(language == 0){
            printf("Use %ssmithy's%s ability, reduce production building cost by one.\n", GRN, RESET);
        }else{
            printf("發動 %s鐵匠鋪%s 能力, 減低一點製造建築的花費\n", GRN, RESET);
        }
        rt = 1;
    }
    return rt;
}

void tower(int playernow, int builtbuilding){
    //Tower 塔樓 (5)
    if(builtbuilding == 5){
        p[playernow].maxcard = 12;
        if(language == 0){
            printf("Use %stower's%s ability, increase max hand cards to 12.\n", GRN, RESET);
        }else{
            printf("發動 %s塔樓%s 能力, 手牌上限增加至12\n", GRN, RESET);
        }
    }
}

void poorhouse(int playernow){
    //Poor House 救濟院 (8)
    if(checkbuilding(playernow, 8)){
        if(p[playernow].cards <= 1){
            p[playernow].deck[p[playernow].cards] = randomcard();
            p[playernow].cards++;
            if(language == 0){
                printf("Use %spoor house's%s ability, get one card when there's one card or less left after building.\n", GRN, RESET);
            }else{
                printf("發動 %s救濟院%s 能力, 蓋完建築後若手牌剩下一張或以下可抽一張卡\n", GRN, RESET);
            }
        }
    }
}

int blackmarket(int playernow, int cost){
    //Black Market 黑市 (9)
    int rt = 0;
    if(checkbuilding(playernow, 9)){
        const string blackmarkettext[2][5] = {{"Do you want to use the ability?", "You chose not use the ability", "Select one good for deduction", "List of buildings that has good", "You skipped this deduction round"},
                                            {"你要使用這項能力嗎?", "你選擇不使用這項能力", "選擇一項資源來扣除花費", "有資源的建築列表", "你跳過了此次選擇機會"} };
        int goods[12] = {-1},sellable = 0;
        int playerhasgoods = 0;
        int choice = 0, invalid = 0;
        int maxcard = 2; 
        if(cost < maxcard){
            maxcard = cost;
        }
        for(int i=0; i<p[playernow].builds; i++){
            if(p[playernow].hasgoods[i] != -1){
                playerhasgoods = 1;
                goods[sellable] = i;
                sellable++;
            }
        }
        if(!playerhasgoods){
            return rt;
        }
        if(p[playernow].isbot == 0){
            while(1){
                CLEAR
                if(language == 0){
                    printf("Use %sblack market's%s ability, sell up to 2 good to reduce cost.\n", GRN, RESET);
                }else{
                    printf("發動 %s黑市%s 能力, 賣出至多兩份的資源來減少建蓋花費\n", GRN, RESET);
                }
                if(invalid) INVALID
                printf("%s\n(1)Yes (0)No \nChoice: ", blackmarkettext[language][0]);
                scanf("%d", &choice);
                FLUSH
                if(choice < 0 || choice > 1){
                    invalid = 1;
                }else{
                    break;
                }
            }   
            if(choice){
                if(sellable < maxcard){
                    maxcard = sellable;
                }
                int totalmaxcard = maxcard;
                while(maxcard){
                    CLEAR
                    printf("%s\n", blackmarkettext[language][3]);
                    printf("=============================\n");
                    for(int i=0; i<sellable; i++){
                        printf("(%d) %s\n", i+1, cardNameData[language][p[playernow].buildings[goods[i]]]);
                    }
                    printf("=============================\n");
                    printf("%s (%d/%d)\n", blackmarkettext[language][2], totalmaxcard-maxcard+1, totalmaxcard);
                    if(invalid) INVALID
                    printf("(0)Skip (1-%d)Select Good\nChoice: ", sellable);
                    scanf("%d", &choice);
                    FLUSH
                    if(choice < 0 || choice > sellable){
                        invalid = 1;
                    }else if(choice){
                        maxcard--;
                        choice--;
                        rt++;
                        int tmpbuilding = goods[choice];
                        p[playernow].hasgoods[goods[choice]] = -1;
                        if(maxcard){
                            for(int i=0; i<p[playernow].builds; i++){
                                if(p[playernow].hasgoods[i] != -1){
                                    goods[sellable] = i;
                                    sellable++;
                                }
                            }
                        }
                        printf("=============================\n");
                        if(language == 0){
                            printf("You sell one good from %s and deduct one cost\n", cardNameData[language][p[playernow].buildings[tmpbuilding]]);
                        }else{
                            printf("你從 %s 賣出了一份資源並減少了一點花費\n", cardNameData[language][p[playernow].buildings[tmpbuilding]]);
                        }
                        PAUSE
                    }else{
                        maxcard--;
                        printf("=============================\n");
                        printf("%s\n", blackmarkettext[language][4]);
                        PAUSE
                    }
                }

            }else{
                printf("=============================\n");
                printf("%s\n", blackmarkettext[language][1]);
                PAUSE
            }
        }else{
            int useability = 0;
            CLEAR
            setcolor(CYN);
            printf("%s\n", botactiontext[language]);
            setcolor(RESET);
            printf("=============================\n");
            if(language == 0){
                printf("Use %sblack market's%s ability, sell up to 2 good to reduce cost.\n", GRN, RESET);
            }else{
                printf("發動 %s黑市%s 能力, 賣出至多兩份的資源來減少建蓋花費\n", GRN, RESET);
            }
            if(useability){
                //lazy (haven't implement)
            }else{
                printf("=============================\n");
                if(language == 0){
                    printf("Player %d chose not to use the ability.\n", playernow+1);
                }else{
                    printf("玩家 %d 選擇不使用能力\n", playernow+1);
                }
                PAUSE
            }
        }

    }

    return rt;
}

void carpenter(int playernow, int builtbuilding){
    //Carpenter 木工場 (11)
    if(type[builtbuilding] != 0 && checkbuilding(playernow, 11)){
        if(language == 0){
            printf("Use %scarpenter's%s ability, get an additional card when building an non-production building.\n", GRN, RESET);
        }else{
            printf("發動 %s木工廠%s 能力, 在建造非生產建築時可抽取一張卡\n", GRN, RESET);
        }
        p[playernow].deck[p[playernow].cards] = randomcard();
        p[playernow].cards++;
    }
}

int quarry(int playernow, int builtbuilding){
    //Quarry 採石場 (12)
    int rt = 0;
    if(type[builtbuilding] != 0 && checkbuilding(playernow, 11)){
        if(language == 0){
            printf("Use %squarry's%s ability, deduct one cost when building a non-prodution building.\n", GRN, RESET);
        }else{
            printf("發動 %s採石場%s 能力, 建造非生產建築時可減少一點花費\n", GRN, RESET);
        }
        rt = 1;
    }
    return rt;
}

void well(int playernow, int producecount){
    //Well 水井 (13)
    if(producecount >= 2 && checkbuilding(playernow, 13)){
        if(language == 0){
            printf("Use %swell's%s ability. If you produce more than two goods, you can get an additional card.\n", GRN, RESET);
        }else{
            printf("發動 %s採石場%s 能力, 當你生產兩個以上的資源,你可以額外抽取一張卡\n", GRN, RESET);
        }
        p[playernow].deck[p[playernow].cards] = randomcard();
        p[playernow].cards++;
    }
}

int aqueduct(int playernow){
    //Aqueduct 溝渠(14)
    int rt = 0;
    if(checkbuilding(playernow, 14)){
        if(language == 0){
            printf("Use %saqueduct's%s ability, you can produce one additional good.\n", GRN, RESET);
        }else{
            printf("發動 %s採石場%s 能力, 你可多額外生產一份資源\n", GRN, RESET);
        }
        rt = 1;
    }
    return rt;
}

void marketstand(int playernow, int sellcount){
    //Market Stand 攤販(15)
    if(sellcount >= 2 && checkbuilding(playernow, 15)){
        if(language == 0){
            printf("Use %smarket stand's%s ability, get one additional card when sold more than one goods.\n", GRN, RESET);
        }else{
            printf("發動 %s攤販%s 能力, 當賣出兩份以上資源時可額外獲得一張卡\n", GRN, RESET);
        }
        p[playernow].deck[p[playernow].cards] = randomcard();
        p[playernow].cards++;
    }
}

void markethall(int playernow){
    //Market Hall 市場 (16)
    if(checkbuilding(playernow, 16)){
        if(language == 0){
            printf("Use %smarket hall's%s ability, get one additional card after trader phase action.\n", GRN, RESET);
        }else{
            printf("發動 %s交易所%s 能力, 在商人階段行動完成後可額外獲得一張卡\n", GRN, RESET);
        }
        p[playernow].deck[p[playernow].cards] = randomcard();
        p[playernow].cards++;
    }
}

int tradingpost(int playernow){
    //Trading Post 交易所 (17)
    int rt = 0;
    if(checkbuilding(playernow, 17)){
        if(language == 0){
            printf("Use %strading post's%s ability, sell one additional good during trader phase.\n", GRN, RESET);
        }else{
            printf("發動 %s交易所%s 能力, 在商人階段可額外售出一份資源\n", GRN, RESET);
        }
        rt = 1;
    }
    return rt;
}

int prefecture(int playernow){
    //Perfecture 辦公處 (19)
    int rt = 0;
    if(checkbuilding(playernow, 19)){
        if(language == 0){
            printf("Use %sperdecture's%s ability, choose one additional card to keep during councilor phase.\n", GRN, RESET);
        }else{
            printf("發動 %s辦公處%s 能力, 在市長階段可額外挑選一張卡\n", GRN, RESET);
        }
        rt = 1;
    }
    return rt;
}

void goldmine(int playernow){
    //Gold mine 金礦坑 (20)
    if(checkbuilding(playernow, 20)){
        int isgold = 1;
        int getcards[4];
        for(int i=0; i<4; i++){
            getcards[i] = randomcard();
        }
        for(int i=0; i<4; i++){
            for(int j=i+1; j<4; j++){
                if(cost[getcards[i]] == cost[getcards[j]]){
                    isgold = 0;
                    break;
                } 
            }
            if(isgold == 0){
                break;
            }
        }
        if(isgold){ 
            if(p[playernow].isbot == 0){
                CLEAR
                int choice, invalid = 0;
                if(language == 0){
                    printf("Use %sgold mine's%s ability, get four cards and if they all have different cost. You can choose one and keep it.\n", GRN, RESET);
                }else{
                    printf("發動 %s金礦坑%s 能力, 抽取四張卡, 如果四張卡的花費皆不同則你可以選擇保留其中一張卡\n", GRN, RESET);
                }
                printf("=============================\n");
                for(int i=0; i<4; i++){
                    printf("(%d) %s Cost:%d VP:%d\n", i+1, cardNameData[language][getcards[i]], cost[getcards[i]], vp[getcards[i]]);
                }
                printf("=============================\n");
                if(language == 0){
                    printf("You got gold :> Choose one card to keep\n");
                }else{
                    printf("你挖到金礦了 :> 選一張卡放入手牌\n");
                }
                if(invalid) INVALID
                printf("Choice: ");
                scanf("%d", &choice);
                FLUSH
                if(choice < 1 || choice > 4){
                    invalid = 1;
                }else{
                    printf("=============================\n");
                    if(language == 0){
                        printf("You chose to keep %s\n", cardNameData[language][getcards[choice-1]]);
                    }else{
                        printf("你選擇保留 %s\n", cardNameData[language][getcards[choice-1]]);
                    }
                    p[playernow].deck[p[playernow].cards] = getcards[choice-1];
                    p[playernow].cards++;
                    getcards[choice-1] = -1;
                    for(int i=0; i<4; i++){
                        if(getcards[i] != -1){
                            discardcard[getcards[i]]++;
                        }
                    }
                    PAUSE
                }
            }else{
                CLEAR
                int choice;
                setcolor(CYN);
                printf("%s\n", botactiontext[language]);
                setcolor(RESET);
                printf("=============================\n");
                if(language == 0){
                    printf("Use %sgold mine's%s ability, get four cards and if they all have different cost. You can choose one and keep it.\n", GRN, RESET);
                }else{
                    printf("發動 %s金礦坑%s 能力, 抽取四張卡, 如果四張卡的花費皆不同則你可以選擇保留其中一張卡\n", GRN, RESET);
                }
                printf("=============================\n");
                choice = rand() % 4;
                p[playernow].deck[p[playernow].cards] = getcards[choice];
                p[playernow].cards++;
                getcards[choice-1] = -1;
                for(int i=0; i<4; i++){
                    if(getcards[i] != -1){
                        discardcard[getcards[i]]++;
                    }
                }
                if(language == 0){
                    printf("Player %d got gold and kept one card\n", playernow+1);
                }else{
                    printf("玩家 %d 挖到金礦並保留了一張卡\n", playernow+1);
                }
                PAUSE
            }
        }else{
            CLEAR
            if(p[playernow].isbot){
                setcolor(CYN);
                printf("%s\n", botactiontext[language]);
                setcolor(RESET);
                printf("=============================\n");
            }
            if(language == 0){
                printf("Use %sgold mine's%s ability, get four cards and if they all have different cost. You can choose one and keep it.\n", GRN, RESET);
            }else{
                printf("發動 %s金礦坑%s 能力, 抽取四張卡, 如果四張卡的花費皆不同則你可以選擇保留其中一張卡\n", GRN, RESET);
            }
            if(language == 0){
                printf("You didn't get gold :<\n");
            }else{
                printf("你沒挖到金礦 :<\\n");
            }
            for(int i=0; i<4; i++){
                discardcard[getcards[i]]++;
            }
            PAUSE
        }
        
    }
}

int guildhall(int playernow){
    //Guild Hall 同業會館 (25)
    int rt = 0;
    if(checkbuilding(playernow, 25)){
        for(int i=0; i<p[playernow].builds; i++){
            if(type[p[playernow].buildings[i]] == 0){
                rt += 2;
            }
        }
    }
    return rt;
}

int cityhall(int playernow){
    //City Hall 市政廳 (26)
    int rt = 0;
    if(checkbuilding(playernow, 26)){
        for(int i=0; i<p[playernow].builds; i++){
            if(type[p[playernow].buildings[i]] != 0){
                rt += 1;
            }
        }
    }
    return rt;
}

int triumhalarch(int playernow){
    //Triumhal Arch 凱旋門 (27)
    int rt = 0, monument = 0;
    if(checkbuilding(playernow, 26)){
        for(int i=0; i<p[playernow].builds; i++){
            if(type[p[playernow].buildings[i]] == 2){
                monument++;
            }
        }
        if(monument == 1){
            rt = 4;
        }else if(monument == 2){
            rt = 6;
        }else if(monument == 3){
            rt = 8;
        }
    }
    return rt;
}

int palace(int playernow, int vpcount){
    //Palace 宮殿 (28)
    int rt = 0;
    if(checkbuilding(playernow, 28)){
        rt = vpcount / 4;
    }
    return rt;
}

void chapels(int playernow){
    //Chapel 禮拜堂 (6)
    const string chapeltext[2][3] = {{"Do you want to use the ability?", "You chose not to use the ability", "You chose"},
                                      {"你要使用這項能力嗎?", "你選擇不使用這項能力", "你選擇了"}};
    if(checkbuilding(playernow, 6)){
        if(p[playernow].isbot == 0){
            CLEAR
            int choice, invalid = 0;
            while(1){
                if(language == 0){
                    printf("Use %schapel's%s ability, place one card under chapel to get one additonal victory point.\n", GRN, RESET);
                }else{
                    printf("發動 %s禮拜堂%s 能力, 將一張卡至於禮拜堂底下以獲得額外一分\n", GRN, RESET);
                }
                printf("=============================\n");
                printf("%s\n(1) Yes (0) No \n", chapeltext[language][0]);
                if(invalid) INVALID
                printf("Choice: ");
                scanf("%d", &choice);
                FLUSH
                if(choice < 0 || choice > 1){
                    invalid = 1;
                }else{
                    break;
                }
            }
            if(choice){
                while(1){
                    CLEAR
                    int choice, invalid = 0;
                    printf("=============================\n");
                    printdeck(playernow);
                    printf("=============================\n");
                    printf("(1-%d) Select Card\n", p[playernow].cards);
                    printf("Choice: ");
                    scanf("%d", &choice);
                    FLUSH
                    if(choice < 1 || choice > p[playernow].cards){
                        invalid = 1;
                    }else{
                        break;
                    }
                    choice--;
                    printf("=============================\n");
                    printf("%s %s", chapeltext[language][2], cardNameData[language][p[playernow].deck[choice]]);
                    PAUSE
                    p[playernow].chapelvp++;
                    p[playernow].deck[choice] = -1;
                    rebuilddeck(playernow);
                }

            }else{
                printf("=============================\n");
                printf("%s\n", chapeltext[language][1]);
                PAUSE
            }

        }else{
            int useability = rand() % 2;
            setcolor(CYN);
            printf("%s\n", botactiontext[language]);
            setcolor(RESET);
            printf("=============================\n");
            if(useability){
                if(language == 0){
                    printf("Use %schapel's%s ability, place one card under the chapel to get one additonal victory point.\n", GRN, RESET);
                }else{
                    printf("發動 %s禮拜堂%s 能力, 將一張卡至於禮拜堂底下以獲得額外一分\n", GRN, RESET);
                }
                int choice = rand() % p[playernow].cards;
                p[playernow].chapelvp++;
                p[playernow].deck[choice] = -1;
                rebuilddeck(playernow);
                printf("=============================\n");
                if(language == 0){
                    printf("Player %d put one card under the chapel.\n", playernow+1);
                }else{
                    printf("玩家 %d 將一張卡放到禮拜堂底下\n", playernow+1);
                }
                PAUSE
            }
        }
    }
}

int library(int playernow, int phase){
    //Library 圖書館 (21)
    int rt = 0;
    if(checkbuilding(playernow, 21)){
        if (phase == 1){
            if(language == 0){
                printf("Use %slibrary's%s ability, reduce cost by two.\n", GRN, RESET);
            }else{
                printf("發動 %s圖書館%s 能力, 減少兩點花費\n", GRN, RESET);
            }
            rt = 2;
        }else if(phase == 2){
            if(language == 0){
                printf("Use %slibrary's%s ability, can produce up to three goods.\n", GRN, RESET);
            }else{
                printf("發動 %s圖書館%s 能力, 最多可生產三份資源\n", GRN, RESET);
            }
            rt = 3;
        }else if(phase == 3){
            if(language == 0){
                printf("Use %slibrary's%s ability, sell up to three goods.\n", GRN, RESET);
            }else{
                printf("發動 %s圖書館%s 能力, 最多可賣出三份資源\n", GRN, RESET);
            }
            rt = 3;
        }else if(phase == 4){
            if(language == 0){
                printf("Use %slibrary's%s ability, get eight cards for selection.\n", GRN, RESET);
            }else{
                printf("發動 %s圖書館%s 能力, 抽取八張牌供選擇\n", GRN, RESET);
            }
            rt = 8;
        }else if(phase == 5){
            if(language == 0){
                printf("Use %slibrary's%s ability, get two cards.\n", GRN, RESET);
            }else{
                printf("發動 %s圖書館%s 能力, 抽取兩張牌\n", GRN, RESET);
            }
            rt = 1;
        }
    }
    return rt;
}

int archive(int playernow, int *cards, int getcards, int keepcards){
    //Archive 檔案館 (18)
    int rt = 0;
    if(checkbuilding(playernow, 18)){
        int discard = getcards - keepcards;
        rt = 1;
        for(int i=0; i<getcards; i++){
            p[playernow].deck[p[playernow].cards] = cards[i];
            p[playernow].cards++;
        }
        int choice, invalid = 0;
        CLEAR
        if(language == 0){
            printf("Use %sarchive's%s ability, adds all card to hand and choose which to discard in councilor phase.\n", GRN, RESET);
        }else{
            printf("發動 %s檔案館%s 能力, 在市長階段中將所有抽到的卡加入手牌在選要捨棄哪些手牌\n", GRN, RESET);
        }
        while(discard){
            printf("=============================\n");
            printdeck(playernow);
            printf("=============================\n");
            if(language == 0){
                printf("Choose one card to discard (%d/%d)\n", getcards - keepcards - discard, getcards-keepcards);
            }else{
                printf("選擇一張牌捨棄 (%d/%d)\n", getcards - keepcards - discard, getcards-keepcards);
            }
            if(invalid) INVALID
            printf("Choice: ");
            scanf("%d", &choice);
            FLUSH
            if(choice < 1 || choice > p[playernow].cards){
                invalid = 1;
            }else{
                choice--;
                discardcard[p[playernow].deck[choice]]++;
                p[playernow].deck[choice] = -1;
                rebuilddeck(playernow);
                discard--;
            }
        }
    }
    return rt;
}

int crane(int playernow){
    //Crane 起重機 (10)
    const string cranetext[2][4] = {{"Do you want to use the ability?", "You chose not to use the ability", "Choose which building to be overbuild", "You chose"},
                                      {"你要使用這項能力嗎?", "你選擇不使用這項能力", "選擇要覆蓋哪個建築", "你選擇了"}};
    int rt = -1;
    if(checkbuilding(playernow, 10)){
        int choice, invalid = 0;
        if(language == 0){
            printf("Use %scrane's%s ability, be able to build on top of other building and pay the cost difference.\n", GRN, RESET);
        }else{
            printf("發動 %s起重機%s 能力, 可覆蓋自己建築物並支付差價\n", GRN, RESET);
        }
        while(1){
            printf("=============================\n");
            printf("%s\n", cranetext[language][0]);
            printf("(1) Yes (0) No\n");
            if(invalid) INVALID
            printf("Choice: ");
            scanf("%d", &choice);
            FLUSH
            if(choice < 0 || choice > 1){
                invalid = 1;
            }else{
                break;
            }
        }
        invalid = 0;
        if(choice){
            while(1){
                CLEAR
                printf("=============================\n");
                printbuilding(playernow);
                printf("=============================\n");
                printf("%s\n", cranetext[language][2]);
                printf("Choice: ");
                scanf("%d", &choice);
                FLUSH
                if(choice < 1 || choice > p[playernow].builds){
                    invalid = 1;
                }else{
                    choice--;
                    break;
                }
            }
            printf("=============================\n");
            printf("%s %s\n", cranetext[language][3], cardNameData[language][p[playernow].buildings[choice]]);
            rt = choice;
        }else{
            printf("=============================\n");
            printf("%s\n", cranetext[language][1]);
            PAUSE
        }
    }
    return rt;
}