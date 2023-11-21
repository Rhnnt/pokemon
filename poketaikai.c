#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//変更しました

typedef struct species{
  char name[20];
  int basehp;
  int baseattack;
  int basedefense;
}species;

typedef struct pokemon{
  char name[100];
  struct species *poketype;
  int level;
  int currentHP;
}pokemon;

species new_species(char[], int, int, int);
pokemon new_pokemon(species*, int);
  void print_poke(pokemon*);
int random_number();
void battle(pokemon*, pokemon*);
int set_nextlist(pokemon *list, int list_nagasa);



int main(){
  srand((unsigned int)time(NULL));
  species pokezukan[10] = {
    {"ピカチュウ", 50, 50, 50},
    {"ピチュー", 30, 30, 30},
    {"ヒトカゲ", 40, 40, 40},
    {"ライチュウ", 50, 50 ,50},
    {"プリン",30,30,30},
    {"カビゴン",20,20,20},
    {"イーブイ",50,50,50},
    {"メタモン",20,20,20},
    {"ラプラス",30,30,30},
    {"マリル",60,60,60}
    
  };
  pokemon *pokelist;
  pokemon *cpu_pokelist;
  int i, list_number;
  int order_det;
  int list_nagasa1, list_nagasa2, list_nagasa;
  pokemon *battle_pokelist;
  int user,cpu;
  
  

  printf("pokelistの長さはいくつにしますか");
  scanf("%d", &list_nagasa);
  list_nagasa1=list_nagasa;
  list_nagasa2=list_nagasa;

  cpu_pokelist = (pokemon*)malloc(list_nagasa2 * sizeof(pokemon));
  for(i=0;i<list_nagasa2;i++){
    list_number = rand()%10 + 1;
    cpu_pokelist[i]=new_pokemon(&pokezukan[list_number],rand()%200+1);
  }
  
  
  pokelist = (pokemon*)malloc(list_nagasa * sizeof(pokemon));
    for(i=0;i<list_nagasa;i++){
      pokelist[i] = new_pokemon(&pokezukan[i],rand()%200+1);
      print_poke(&pokelist[i]);
    }
  

  battle_pokelist = (pokemon*)malloc(list_nagasa1 * sizeof(pokemon));
  for(i=0;i<list_nagasa1;i++){
    printf("%d番目のポケモンを選んでください",i+1);
    scanf("%d",&order_det);
    battle_pokelist[i] = pokelist[order_det];
   }

  //for(i=0;i<list_nagasa;i++){
  //  print_poke(&battle_pokelist[i]);
  //}

  if(list_nagasa1>0&&list_nagasa2>0){
    for(i=0;i<list_nagasa;i++){
      battle(&battle_pokelist[i], &cpu_pokelist[i]);
      set_nextlist(battle_pokelist,list_nagasa1);
      set_nextlist(cpu_pokelist,list_nagasa2);
    }
  }else{
    user = set_nextlist(battle_pokelist,list_nagasa1);
    cpu = set_nextlist(cpu_pokelist,list_nagasa2);
    if(user>cpu){
      printf("あなたの勝ちです");
    }else if(cpu>user){
      printf("CPUの勝ちです");
    }else{
      printf("引き分けです");
    }
  }
  
  free(pokelist);
  free(cpu_pokelist);
  free(battle_pokelist);
    return 0;
}

pokemon new_pokemon(species *poke_type, int level){
  pokemon chara;
  int i;
  chara.poketype = poke_type;
  chara.level = level;
  for(i=0;i<20;i++){
    chara.name[i] = poke_type->name[i];
  }
  
  chara.currentHP = chara.poketype->basehp;
  return chara;
}

void print_poke(pokemon* poke){
  printf("Character:%s(species: %s)level: %d HP:%d/%d\n", poke->name, poke->poketype->name,poke->level,poke->currentHP,poke->poketype->basehp);
}

void battle(pokemon *a, pokemon *b){
  int aatk = a->poketype->baseattack*100*a->level/(100+a->level);
  int bdef = b->poketype->basedefense*100*b->level/(100+b->level);
  int adamage = aatk-bdef;
  int batk = b->poketype->baseattack*100*b->level/(100+b->level);
  int adef = a->poketype->basedefense*100*a->level/(100+a->level);
  int bdamage = batk-adef;
  if(adamage<1){
    adamage=1;
  }
  if(bdamage<1){
    bdamage=1;
  }
  while(a->currentHP > 0 && b-> currentHP > 0){
    
    b->currentHP = b->currentHP - adamage;
    a->currentHP = b->currentHP - bdamage;

    if(b->currentHP<0){
      b->currentHP=0;
    }
     if(a->currentHP<0){
      a->currentHP=0;
    }
  }

  printf("ユーザーのポケモンのHP: %d",a->currentHP);
  printf("CPUのポケモンのHP: %d",b->currentHP);
  //if(b->currentHP<=0){
  //  a->level++;
  //  cpu_pokelist = (pokemon*)realloc(list_nagasa-1 * sizeof(pokemon));
  //}
  //if(a->currentHP<=0){
  //  b->level++;
  //  cpu_pokelist = (pokemon*)realloc(list_nagasa-1 * sizeof(pokemon));
  //}
}

int set_nextlist(pokemon *list, int list_nagasa){
  int i,j;
  int counter = 0;
  pokemon tmp;
  for(i=0;i<list_nagasa-1;i++){
    if(list[i].currentHP<=0){
      counter++;
      for(j=i+1;j<=list_nagasa-1;j++){
	tmp = list[j-1];
	list[j-1] = list[j];
      }
      list_nagasa-=counter;
      list = (pokemon*)realloc(list, sizeof(pokemon)*list_nagasa);
      
    }
  }
  free(list);
  return counter;
}



