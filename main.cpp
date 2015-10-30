#include<allegro.h>
#define speed 4
/*
         Header files to index the datafiles
*/
#include "data.h"
#include "openpg.h"

/*
         Functions to intialize and uninitialize objects
*/
void init();
void deinit();

/*
          Bitmap pointers to point to the bitmap images
*/
BITMAP *bmp;
BITMAP *box;
BITMAP *tembmp;
BITMAP *backgrnd;
BITMAP *gateclos;
BITMAP *gateopen;
BITMAP *hiscr;
BITMAP *tem_enemy;

/*
         Datafile pointers to point to the datafiles
*/
DATAFILE *data;
DATAFILE *main_pg;
//DATAFILE *credits;

int points=0;    // To store the points

/* Some idetifiers for miscellaneous purpose */
int delay_man=-1;
clock_t ti1=0,ti2=0;
int num_enemy;
int ene_speed;

/* color variables */
int noentry,man,bord,_box,__enemy,_blast,_bomb;
int man_status;
int color_game[6];
enum{NOENTRY,MAN,BORD,_BOX,DEATH,_BLAST,_BOMB};
int color_enemy[6];

/* Idetifiers for plscements and timers */
int initial[15][19]=
{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
  -1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1,
  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
  -1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1,
  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
  -1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1,
  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
  -1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1,
  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
  -1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1,
  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
  -1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1,
  -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
};
int background[15][19];
/////////values for placements///////////
/*
free space=0;
box=1;
border=-1;
bomb1=2;
bomb2=3;

*/

/*
          Structure to store the images pixelwise
*/
struct imager
{
    int x,y,col;
};

//////////////////////////////////////////////////////////////void initialiser()////////////////////////////////////////////////////////
void initialiser()
{
    int i,j;
    for(i=0;i<15;i++)
        for(j=0;j<19;j++)
             background[i][j]=initial[i][j];
    blit((BITMAP*)data[bktem].dat,tembmp,0,0,0,0,640,480);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////class bomber_man/////////////////////////////////////////////////////
class bomber_man
{
    private:
        int xcord;
        int ycord;
    public:
        bomber_man();
        int move();
        void printman(int ch);
        void level(int leve);
        void check_move(int,int);
};

bomber_man::bomber_man()
{
        xcord=48;
        ycord=52;
}

void bomber_man::check_move(int xt,int yt)
{
       int xtem1,ytem1,i;
       for(i=0;i<6;i++)
             color_game[i]=0;
       if(yt<0)
       for(xtem1=xcord+xt,ytem1=ycord+yt;xtem1<xcord+xt+32;xtem1++)
       {      
              if(getpixel(tembmp,xtem1,ytem1)==noentry)
              {      
                     color_game[NOENTRY]=1;
                     color_game[MAN]=1;
              }
              if(getpixel(tembmp,xtem1,ytem1)==bord)
              {
                     color_game[BORD]=1;
                     color_game[MAN]=1;
              }
              if(getpixel(tembmp,xtem1,ytem1)==_box)
              {
                     color_game[_BOX]=1;
                     color_game[MAN]=1;
              }
       }                                                            
       if(xt>0)
       for(xtem1=xcord+xt+31,ytem1=ycord+yt;ytem1<ycord+yt+32;ytem1++)
       {      
              if(getpixel(tembmp,xtem1,ytem1)==noentry)
              {      
                     color_game[NOENTRY]=1;
                     color_game[MAN]=1;
              }
              if(getpixel(tembmp,xtem1,ytem1)==bord)
              {
                     color_game[BORD]=1;
                     color_game[MAN]=1;
              }
              if(getpixel(tembmp,xtem1,ytem1)==_box)
              {
                     color_game[_BOX]=1;
                     color_game[MAN]=1;
              }
       }
       if(yt>0)
       for(xtem1=xcord+xt+31,ytem1=ycord+yt+31;xtem1>=xcord+xt;xtem1--)
       {      
              if(getpixel(tembmp,xtem1,ytem1)==noentry)
              {      
                     color_game[NOENTRY]=1;
                     color_game[MAN]=1;
              }
              if(getpixel(tembmp,xtem1,ytem1)==bord)
              {
                     color_game[BORD]=1;
                     color_game[MAN]=1;
              }
              if(getpixel(tembmp,xtem1,ytem1)==_box)
              {
                     color_game[_BOX]=1;
                     color_game[MAN]=1;
              }
       } 
       if(xt<0)
       for(xtem1=xcord+xt,ytem1=ycord+yt+31;ytem1>=ycord+yt;ytem1--)
       {      
              if(getpixel(tembmp,xtem1,ytem1)==noentry)
              {      
                     color_game[NOENTRY]=1;
                     color_game[MAN]=1;
              }
              if(getpixel(tembmp,xtem1,ytem1)==bord)
              {
                     color_game[BORD]=1;
                     color_game[MAN]=1;
              }
              if(getpixel(tembmp,xtem1,ytem1)==_box)
              {
                     color_game[_BOX]=1;
                     color_game[MAN]=1;
              }
              
       }
       for(xtem1=xcord+xt,ytem1=ycord+yt+31;ytem1>=ycord+yt;ytem1--)
       if(getpixel(tembmp,xtem1,ytem1)==__enemy||getpixel(tembmp,xtem1,ytem1)==_blast)
               color_game[DEATH]=1;
       for(xtem1=xcord+xt+31,ytem1=ycord+yt+31;xtem1>=xcord+xt;xtem1--)
       if(getpixel(tembmp,xtem1,ytem1)==__enemy||getpixel(tembmp,xtem1,ytem1)==_blast)
               color_game[DEATH]=1;
       for(xtem1=xcord+xt+31,ytem1=ycord+yt;ytem1<ycord+yt+32;ytem1++)
       if(getpixel(tembmp,xtem1,ytem1)==__enemy||getpixel(tembmp,xtem1,ytem1)==_blast)
               color_game[DEATH]=1;
       for(xtem1=xcord+xt,ytem1=ycord+yt;xtem1<xcord+xt+32;xtem1++)
       if(getpixel(tembmp,xtem1,ytem1)==__enemy||getpixel(tembmp,xtem1,ytem1)==_blast)
               color_game[DEATH]=1;
       
}

void bomber_man::printman(int ch)         //To print the man
{
    int i,j;
    masked_blit((BITMAP*)data[ch].dat,bmp,0,0,xcord,ycord-11,640,480);
}

int bomber_man::move()
{
    static int xt=0,yt=0,ch,img=0,deter=0,i=0;
    static float x1=0,y1=0,x2=0,y2=0;
    time_t timee;
    if(!color_game[DEATH])
    {
        if(key[KEY_UP])
            yt=-speed;
        else
        if(key[KEY_DOWN])
            yt=speed;
        else
        if(key[KEY_LEFT])
            xt=-speed;
        else
        if(key[KEY_RIGHT])
            xt=speed;
        else
        img=1;
        
        if(key[KEY_SPACE]&&background[(ycord+16-52)/32+1][(xcord+16-48)/32+1]<100&&background[(ycord+16-52)/32+1][(xcord+16-48)/32+1]!=6)
        {
            background[(ycord+16-52)/32+1][(xcord+16-48)/32+1]=100;                 
            rectfill(tembmp,((xcord+16-48)/32)*32+48,((ycord+16-52)/32)*32+52,((xcord+16-48)/32)*32+48+31,((ycord+16-52)/32)*32+52+31,_bomb);
        }
        
        
        if(background[(ycord+16-52)/32+1][(xcord+16-48)/32+1]==6&&num_enemy==0&&deter!=1)
        {       
                deter=1;
                x1=((xcord-48+16)/32)*32+48+16;
                y1=((ycord-52+16)/32)*32+52+8+16;
                x2=16;
                y2=43-16;
        }

        
        if(deter==0)
        {
            check_move(xt,yt);
            if(!color_game[MAN])
            {
                      xcord+=xt;
                      ycord+=yt;
            }
            else
            {
                if(color_game[BORD])
                {
                      if(xt!=0&&(((ycord-52)%64)>=32))
                      {
                            xt=0;
                            yt=speed;                              
                      }
                      else
                      if(xt!=0&&((ycord-52)%64)<32)
                      {
                            xt=0;
                            yt=-speed;                              
                      }
                      else
                      if(yt!=0&&(((xcord-48)%64)>=32))
                      {
                            xt=speed;
                            yt=0;                              
                      }
                      else
                      if(yt!=0&&((xcord-48)%64)<32)
                      {
                            xt=-speed;
                            yt=0;                              
                      }
                }
                if((xt<0&&xcord<50)||(xt>0&&xcord>586)||(yt<0&&ycord<54)||(yt>0&&ycord>466))
                {
                      xt=0;
                      yt=0;                                                                                                                                                          
                }
                check_move(xt,yt);
                if(!color_game[MAN])
                {
                      xcord+=xt;
                      ycord+=yt;
                }         
            }
            img+=speed;
            if(img>speed*12)
                img=1;
            if(xt<0)
                    ch=0;        
            if(xt>0)
                    ch=6;
            if(yt<0)
                    ch=9;
            if(yt>0)
                    ch=3;
            if(img>0&&img<=speed*3)
            printman(ch);
            if(img>speed*3&&img<=speed*6)
            printman(ch+1);
            if(img>speed*6&&img<=speed*9)
            printman(ch);
            if(img>speed*9&&img<=speed*12)
            printman(ch+2);
            xt=0;
            yt=0;       
        }
        
        if(deter==1)
        {
            if(i==30)
            {
                  deter=0;
                  i=0;
                  return 1;   
            }
            if(i%12<3)  
                 ch=bomb10;
            else
            if(i%12<6)  
                 ch=bomb10+1;
            else
            if(i%12<9)  
                 ch=bomb10;
            else
                 ch=bomb10+2;     
            
            x2-=0.32;
            y2-=0.43;
            
            masked_stretch_blit((BITMAP*)data[ch].dat,bmp,0,0,32,43,x1-x2,y1-y2,2*x2,y2+x2);
            i++;    
        } 
    
    }
    
    else
        if(man_status==0)
                man_status=2;
    
    if(man_status>1)
    { 
        man_status++;
        masked_stretch_blit((BITMAP*)data[mandead].dat,bmp,0,0,32,43,xcord+16-0.32*(50-man_status),ycord+21-0.43*(50-man_status),2*0.32*(50-man_status),2*0.43*(50-man_status));       
        if(man_status==50)
            man_status=1;
    }
    return 0;
}

void bomber_man::level(int leve)
{
     xcord=48;
     ycord=52;
     unsigned int i,j,k;
     for(i=0;i<6;i++)
         color_game[i]=0;
     background[1][1]=11;
     background[1][2]=11;
     background[2][1]=11;
     switch(leve)
     {
          case 1:
              for(i=0,j=0,k=0;k<45;)
              {
                  srand(clock());
                  i=rand();
                  srand(clock()*i);
                  j=rand();                      
                  i=i%15;
                  j=j%19;
                  if(background[i][j]==0)
                  {
                       {
                                background[i][j]=1;
                                k++;
                       }
                  }                  
              }
              break;
          case 2:
               for(i=0,j=0,k=0;k<40;)
              {
                  srand(clock());
                  i=rand();
                  srand(clock()*i);
                  j=rand();                      
                  i=i%15;
                  j=j%19;
                  if(background[i][j]==0)
                  {
                       {
                                background[i][j]=1;
                                k++;
                       }
                  }                  
              }  
              break;
          case 3:
               for(i=0,j=0,k=0;k<35;)
              {
                  srand(clock());
                  i=rand();
                  srand(clock()*i);
                  j=rand();                      
                  i=i%15;
                  j=j%19;
                  if(background[i][j]==0)
                  {
                       {
                                background[i][j]=1;
                                k++;
                       }
                  }                  
              }  
              break;
           default:
                for(i=0,j=0,k=0;k<25;)
              {
                  srand(clock());
                  i=rand();
                  srand(clock()*i);
                  j=rand();                      
                  i=i%15;
                  j=j%19;
                  if(background[i][j]==0)
                  {
                       {
                                background[i][j]=1;
                                k++;
                       }
                  }                  
              }    
              break;
     }
     background[i][j]=5;
     background[1][1]=0;
     background[1][2]=0;
     background[2][1]=0;
}
//////////////////////////////////////////////////////End of the class bomber_man/////////////////////////////////////////////

/////////////////////////////////////////////////int ifman_dead()///////////////////////////////////////////////////////////
int ifman_dead()
{
     int x,y,tcol,r,g,b;
     float per=0.2;
     for(y=0;y<768;y++)
     {
            for(x=0;x<1024;x++)
            {
                    tcol=getpixel(bmp,x,y);
                    r=getr(tcol)*per;
                    g=getg(tcol)*per;
                    b=getb(tcol)*per;
                    putpixel(bmp,x,y,makecol(r,g,b));         
            }                 
     }
     blit((BITMAP*)data[ifmandead].dat,bmp,0,0,192,144,256,192);
     blit((BITMAP*)data[yes1].dat,bmp,0,0,231,286,50,20);
     blit((BITMAP*)data[no1].dat,bmp,0,0,359,286,50,20);
     position_mouse(320,240);
     blit(bmp,screen,0,0,0,0,640,480);
     unscare_mouse();
     while(!key[KEY_ESC])
     { 
     			unscare_mouse();
                if(mouse_x>231&&mouse_x<281&&mouse_y>286&&mouse_y<306)
                { 
                       vsync();
                       scare_mouse();
                       blit((BITMAP*)data[yes2].dat,screen,0,0,228,284,55,23);
                       unscare_mouse();
                       if (mouse_b & 1)
                           return 1;      
                }
                else
                if(mouse_x>359&&mouse_x<409&&mouse_y>286&&mouse_y<306)
                { 
                       vsync();
                       scare_mouse();
                       blit((BITMAP*)data[no2].dat,screen,0,0,356,284,55,23);
                       unscare_mouse();
                       if (mouse_b & 1)
                           return 2;      
                }
                else
                {
                    vsync();
                    scare_mouse();
                    blit(bmp,screen,0,0,0,0,640,480);
                    unscare_mouse();
                }
     }
     return 2;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////class enemy/////////////////////////////////////////////////////////////
class enemy
{
    private:
          int xcord[10];
          int ycord[10];   //stores the position of the ith enemy
          int xt[10];
          int yt[10];      
          int status[10];  //stures the health status the the ith enemy
          int n_enemy;     // keeps the count of number of enemies 
    public:
          enemy();   
          void level(int);
          void move();
          void check_move(int xt,int yt,int i);
          void drawenemy(int mn,int i);
     
};

// Constructor
enemy::enemy()
{      
                             
}

// Creates a new level
void enemy::level(int leve)
{
     unsigned int i,j,k;
     for(i=0;i<10;i++)
        status[i]=1;   
     switch(leve)
     {
           case 1:
                n_enemy=4;
                num_enemy=4;
                ene_speed=2;
                for(i=0,j=0,k=0;k<n_enemy;)
                {
                  srand(clock());
                  i=rand();
                  srand(clock()*i);
                  j=rand();                      
                  i=i%15;
                  j=j%19;
                  if(background[i][j]==0)
                  {
                        xcord[k]=48+(j-1)*32;
                        ycord[k]=52+(i-1)*32;
                        xt[k]=0;     
                        yt[k]=2;
                        k++;            
                        background[i][j]=9;                 
                  }
                }
                for(k=0;k<n_enemy;k++)
                {
                    background[(ycord[k]-45)/32+1][(xcord[k]-40)/32+1]=0;                      
                }
                break;
           case 2:
                n_enemy=6;
                num_enemy=6;
                ene_speed=2;
                for(i=0,j=0,k=0;k<n_enemy;)
                {
                  srand(clock());
                  i=rand();
                  srand(clock()*i);
                  j=rand();                      
                  i=i%15;
                  j=j%19;
                  if(background[i][j]==0)
                  {
                        xcord[k]=48+(j-1)*32;
                        ycord[k]=52+(i-1)*32;
                        xt[k]=0;     
                        yt[k]=2;
                        k++;            
                        background[i][j]=9;                 
                  }
                }
                for(k=0;k<n_enemy;k++)
                {
                    background[(ycord[k]-45)/32+1][(xcord[k]-40)/32+1]=0;                      
                }
                break;
           case 3:
                n_enemy=6;
                num_enemy=6;
                ene_speed=3;
                for(i=0,j=0,k=0;k<n_enemy;)
                {
                  srand(clock());
                  i=rand();
                  srand(clock()*i);
                  j=rand();                      
                  i=i%15;
                  j=j%19;
                  if(background[i][j]==0)
                  {
                        xcord[k]=48+(j-1)*32;
                        ycord[k]=52+(i-1)*32;
                        xt[k]=0;     
                        yt[k]=4;
                        k++;            
                        background[i][j]=9;                 
                  }
                }
                for(k=0;k<n_enemy;k++)
                {
                    background[(ycord[k]-45)/32+1][(xcord[k]-40)/32+1]=0;                      
                }
                break;
           default:
                n_enemy=8;
                num_enemy=8;
                ene_speed=4;
                for(i=0,j=0,k=0;k<n_enemy;)
                {
                  srand(clock());
                  i=rand();
                  srand(clock()*i);
                  j=rand();                      
                  i=i%15;
                  j=j%19;
                  if(background[i][j]==0)
                  {
                        xcord[k]=48+(j-1)*32;
                        ycord[k]=52+(i-1)*32;
                        xt[k]=0;     
                        yt[k]=4;
                        k++;            
                        background[i][j]=9;                 
                  }
                }
                for(k=0;k<n_enemy;k++)
                {
                    background[(ycord[k]-45)/32+1][(xcord[k]-40)/32+1]=0;                      
                }
                break;
     }    


}

// Prints the enemies
void enemy::drawenemy(int ch,int i)
{
     static int xa[10],ya[10];
     masked_blit((BITMAP*)data[ch+enemy1].dat,bmp,0,0,xcord[i],ycord[i]-6,640,480);
     rectfill(tembmp,xa[i],ya[i],xa[i]+31,ya[i]+31,man);
     xa[i]=xcord[i];
     ya[i]=ycord[i];
     rectfill(tembmp,xa[i],ya[i],xa[i]+31,ya[i]+31,__enemy);
}

// Moves the enemies
void enemy::move()
{
     static int i,xte,yte,img=1;
     img++;
     if(img>=20)
     img=1;     
     for(i=0;i<n_enemy;i++)
     {
           if(status[i]==1)
           {            
                        xte=0;
                        yte=0;
                        check_move(xt[i],yt[i],i);
                        if(!color_enemy[0])
                        {
                               xcord[i]+=xt[i];
                               ycord[i]+=yt[i];                    
                        }    
                        else
                        {
                               unsigned int cho;
                               time_t t;
                               cho=(unsigned)time(&t);
                               srand(cho);
                               cho=rand();
                               cho=cho%4;
                               xt[i]=0;
                               yt[i]=0;
                               switch(cho)
                               {
                                      case 0:
                                              xt[i]=-ene_speed;break;
                                      case 1:
                                              xt[i]=ene_speed;break;
                                      case 2:
                                              yt[i]=-ene_speed;break;
                                      case 3:
                                              yt[i]=ene_speed;break;           
                               }
                               check_move(xt[i],yt[i],i);
                               if(!color_enemy[0])
                               {
                                      xcord[i]+=xt[i];
                                      ycord[i]+=yt[i];                    
                               }               
                        }
                        drawenemy(img/5,i);
                        if(color_enemy[1])
                        {
                                status[i]=2;
                                rectfill(tembmp,xcord[i],ycord[i],xcord[i]+31,ycord[i]+31,man);
                                num_enemy--;
                                points+=100;
                        }
           }
           if(status[i]>1)
           {
                status[i]++;
                masked_stretch_blit((BITMAP*)data[enemydead].dat,bmp,0,0,28,34,xcord[i]+14-0.28*(50-status[i]),ycord[i]+17-0.34*(50-status[i]),2*0.28*(50-status[i]),2*0.34*(50-status[i]));   
                
                if(status[i]==50)
                     status[i]=0;               
                     textout_ex(bmp,font,"100",xcord[i],ycord[i],makecol(255,255,255),makecol(0,0,0));       
           }
     }
}

// Checks the moves for enemies
void enemy::check_move(int xt,int yt,int i)
{
       int xtem1=xcord[i]+xt,ytem1=ycord[i]+yt;
       int j;
       for(j=0;j<6;j++)
              color_enemy[j]=0;
       if(yt<0)
       for(xtem1=xcord[i]+xt,ytem1=ycord[i]+yt;xtem1<xcord[i]+xt+32;xtem1++)
       {      
              if(getpixel(tembmp,xtem1,ytem1)!=man)
                     color_enemy[0]=1;
       }
                                                          
       if(xt>0)
       for(xtem1=xcord[i]+xt+31,ytem1=ycord[i]+yt;ytem1<ycord[i]+yt+32;ytem1++)
       {      
              if(getpixel(tembmp,xtem1,ytem1)!=man)
                     color_enemy[0]=1;
       }
       if(yt>0)
       for(xtem1=xcord[i]+xt+31,ytem1=ycord[i]+yt+31;xtem1>=xcord[i]+xt;xtem1--)
       {      
              if(getpixel(tembmp,xtem1,ytem1)!=man)
                     color_enemy[0]=1;             
       } 
       if(xt<0)
       for(xtem1=xcord[i]+xt,ytem1=ycord[i]+yt+31;ytem1>=ycord[i]+yt;ytem1--)
       {      
              if(getpixel(tembmp,xtem1,ytem1)!=man)
                     color_enemy[0]=1;
       }  
       for(xtem1=xcord[i]+xt,ytem1=ycord[i]+yt;xtem1<xcord[i]+xt+32;xtem1++)
              if(getpixel(tembmp,xtem1,ytem1)==_blast)
                     color_enemy[1]=1;
       for(xtem1=xcord[i]+xt+31,ytem1=ycord[i]+yt;ytem1<ycord[i]+yt+32;ytem1++)
              if(getpixel(tembmp,xtem1,ytem1)==_blast)
                     color_enemy[1]=1;
       for(xtem1=xcord[i]+xt+31,ytem1=ycord[i]+yt+31;xtem1>=xcord[i]+xt;xtem1--)
              if(getpixel(tembmp,xtem1,ytem1)==_blast)
                     color_enemy[1]=1;
       for(xtem1=xcord[i]+xt,ytem1=ycord[i]+yt+31;ytem1>=ycord[i]+yt;ytem1--)
              if(getpixel(tembmp,xtem1,ytem1)==_blast)
                     color_enemy[1]=1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////class bomb///////////////////////////////////////////////////////////////
class bomb
{
     private:
             imager blast[3][5120];  //To store the image of blast
             int bla[3];
     public:
            void print_bomb(int x,int y,int ch);
            void print_blast(int x,int y,int ch);
            void remove_blast(int x,int y);
            bomb();  
};

bomb::bomb()
{
     int x,y,i;    
     for(x=0,y=0,bla[0]=0;y<96;x++)
     {
          if(x==96)
          {
               x=0;
               y++;        
          }        
          if(getpixel((BITMAP*)data[blast1].dat,x,y)!=man)
          {
               blast[0][bla[0]].x=x-32;                             
               blast[0][bla[0]].y=y-32;
               blast[0][bla[0]].col=getpixel((BITMAP*)data[blast1].dat,x,y);
               bla[0]++;
          }
     }    
     for(x=0,y=0,bla[1]=0;y<96;x++)
     {
          if(x==96)
          {
               x=0;
               y++;        
          }        
          if(getpixel((BITMAP*)data[blast2].dat,x,y)!=man)
          {
               blast[1][bla[1]].x=x-32;                             
               blast[1][bla[1]].y=y-32;
               blast[1][bla[1]].col=getpixel((BITMAP*)data[blast2].dat,x,y);
               bla[1]++;
          }
     }     
     for(x=0,y=0,bla[2]=0;y<96;x++)
     {
          if(x==96)
          {
               x=0;
               y++;        
          }        
          if(getpixel((BITMAP*)data[blast3].dat,x,y)!=man)
          {
               blast[2][bla[2]].x=x-32;                             
               blast[2][bla[2]].y=y-32;
               blast[2][bla[2]].col=getpixel((BITMAP*)data[blast3].dat,x,y);
               bla[2]++;
          }
     }
}

void bomb::print_bomb(int x,int y,int ch)
{
     int i,y1;
     if(ch==0)
          y1=-3;
     if(ch==1)
          y1=-6;
     masked_blit((BITMAP*)data[bom1+ch].dat,bmp,0,0,x,y+y1,640,480);     
}

void bomb::print_blast(int x,int y,int ch)
{
     int i,tem,pont;
     pont=0;
     for(i=0;i<bla[ch];i++)
     {
         tem=getpixel(tembmp,blast[ch][i].x+x,blast[ch][i].y+y);
         if(tem==man||tem==_box||tem==__enemy||tem==_blast)
         {
               putpixel(bmp,blast[ch][i].x+x,blast[ch][i].y+y,blast[ch][i].col);
               putpixel(tembmp,blast[ch][i].x+x,blast[ch][i].y+y,_blast);
         }
         if(tem==_box)
         {
               pont+=50;       
               points+=pont;         
               if(background[(blast[ch][i].y+y-52)/32+1][(blast[ch][i].x+x-48)/32+1]==1)
                      background[(blast[ch][i].y+y-52)/32+1][(blast[ch][i].x+x-48)/32+1]=pont*1000;
               if(background[(blast[ch][i].y+y-52)/32+1][(blast[ch][i].x+x-48)/32+1]==5)
                      background[(blast[ch][i].y+y-52)/32+1][(blast[ch][i].x+x-48)/32+1]=6;
               rectfill(tembmp,((blast[ch][i].x+x-48)/32)*32+48,((blast[ch][i].y+y-52)/32)*32+52,((blast[ch][i].x+x-48)/32)*32+31+48,((blast[ch][i].y+y-52)/32)*32+31+52,man);
         }
     }
}

void bomb::remove_blast(int x,int y)
{
     int i,tem;
     for(i=0;i<bla[2];i++)
     {
         tem=getpixel(tembmp,blast[2][i].x+x,blast[2][i].y+y);
         if(tem==_blast)                     
         putpixel(tembmp,blast[2][i].x+x,blast[2][i].y+y,man);
     }
}
///////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////Box_maker()///////////////////////////////////////
void box_maker()
{   int i,j;
    static bomb bomm;
    for(i=0;i<15;i++)
        for(j=0;j<19;j++)
        {
             if(background[i][j]==1||background[i][j]==5)
             {
                   blit(box,bmp,0,0,48+32*(j-1),52+32*(i-1),640,480);
                   rectfill(tembmp,48+32*(j-1),52+32*(i-1),48+31+32*(j-1),52+31+32*(i-1),_box);
             }      
             if(background[i][j]==6)
             {
                   blit(gateclos,bmp,0,0,48+32*(j-1),52+32*(i-1),640,480);                 
             }
             if(background[i][j]==6&&num_enemy==0)
             {
                   blit(gateopen,bmp,0,0,48+32*(j-1),52+32*(i-1),640,480);                                                    
             }
             if(background[i][j]/50000>0)
             {
                     if(background[i][j]%50000==30)
                         background[i][j]=0; 
                     else
                     {   
                         char str[]="000";
                         int tee;
                         tee=50*background[i][j]/50000;
                         str[2]=tee%10+48;
                         tee/=10;
                         str[1]=tee%10+48;
                         tee/=10;
                         str[0]=tee+48;
                         textout_ex(bmp,font,str,(j-1)*32+52,(i-1)*32+48,makecol(255,255,255),makecol(0,0,0));    
                         background[i][j]++;
                     }                           
             }
        }
        
    for(i=0;i<15;i++)
        for(j=0;j<19;j++)
        {
             if(background[i][j]>=100&&background[i][j]<150)
             {
                   background[i][j]++;
                   if((background[i][j]/10)%2==1)
                   {
                          bomm.print_bomb((j-1)*32+48,(i-1)*32+52,1);
                   }                    
                   else
                   {
                          bomm.print_bomb((j-1)*32+48,(i-1)*32+52,0);
                   }                           
             }
             if(background[i][j]==150)
                   rectfill(tembmp,(j-1)*32+48,(i-1)*32+52,(j-1)*32+48+31,(i-1)*32+52+31,man);
             if(background[i][j]>=150&&background[i][j]<158)
             {
                   background[i][j]++;
                   if((background[i][j]-150)/2==0)
                   {
                          bomm.print_blast((j-1)*32+48,(i-1)*32+52,0);
                   }                    
                   if((background[i][j]-150)/2==1)
                   {
                          bomm.print_blast((j-1)*32+48,(i-1)*32+52,1);
                   }
                   if((background[i][j]-150)/2==2||(background[i][j]-150)/2==3)
                   {
                          bomm.print_blast((j-1)*32+48,(i-1)*32+52,2);
                   }                           
             }
             if(background[i][j]==158)
             {
                   bomm.remove_blast((j-1)*32+48,(i-1)*32+52);
                   background[i][j]=0;                
             }
        }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////int main_page()////////////////////////////////////////////////////////////////////////
int main_page()
{
        blit((BITMAP*)main_pg[bkgnd].dat,bmp,0,0,0,0,640,480);
        blit((BITMAP*)main_pg[play1].dat,bmp,0,0,120,50,400,50);
        blit((BITMAP*)main_pg[high1].dat,bmp,0,0,120,150,400,50);
        blit((BITMAP*)main_pg[help1].dat,bmp,0,0,120,250,400,50);
        //blit((BITMAP*)main_pg[cred1].dat,bmp,0,0,120,350,400,50);
        masked_blit((BITMAP*)main_pg[exit1].dat,bmp,0,0,30,410,40,40);
        blit(bmp,screen,0,0,0,0,640,480);
        int x=0,y=0,count=0;
        unscare_mouse();
        while(!key[KEY_ESC])
        {       
                if(mouse_x>120&&mouse_x<520&&mouse_y>50&&mouse_y<100)
                { 
                       vsync();
                       scare_mouse();
                       blit((BITMAP*)main_pg[play2].dat,screen,0,0,110,48,420,55);
                       if (mouse_b & 1)
                           return 1;                               
                       unscare_mouse();
                       x=48;y=48;
                }
                else
                if(mouse_x>120&&mouse_x<520&&mouse_y>150&&mouse_y<200)
                {                        
                       vsync();
                       scare_mouse();
                       blit((BITMAP*)main_pg[high2].dat,screen,0,0,110,148,420,55);                               
                       if (mouse_b & 1)
                           return 2;      
                       unscare_mouse();           
                       x=48;y=148;                
                }
                else
                if(mouse_x>120&&mouse_x<520&&mouse_y>250&&mouse_y<300)
                {    
                       vsync();
                       scare_mouse();
                       blit((BITMAP*)main_pg[help2].dat,screen,0,0,110,248,420,55);                               
                       if (mouse_b & 1)
                           return 3;
                       unscare_mouse();
                       x=48;y=248;
                }
               /* else
                if(mouse_x>120&&mouse_x<520&&mouse_y>350&&mouse_y<400)
                { 
                       vsync();
                       scare_mouse();
                       blit((BITMAP*)main_pg[cred2].dat,screen,0,0,110,348,420,55);                               
                       if (mouse_b & 1)
                           return 4;
                       unscare_mouse();
                       x=48;y=348;
                }*/
                else
                if(vector_length_f(mouse_x-50,mouse_y-430,0)<20)
                {
                      vsync();
                      scare_mouse();
                      masked_blit((BITMAP*)main_pg[exit2].dat,screen,0,0,29,409,43,43);
                      unscare_mouse();
                       if (mouse_b & 1)
                           return 5;                                          
                }
                else
                {
                    vsync();
                    scare_mouse();
                    blit(bmp,screen,0,0,0,0,640,480);
                    unscare_mouse();
                    x=0;y=0;
                }
                if(x&&y)
                {
                            stretch_blit((BITMAP*)main_pg[blas1+count/20].dat,screen,0,0,96,96,48,y,55,55);
                            stretch_blit((BITMAP*)main_pg[blas1+count/20].dat,screen,0,0,96,96,532,y,55,55);
                            count++;
                            if(count==60)
                                         count=0;        
                }
        }
        return 5;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////void help()///////////////////////////////////////////
void helper()
{
      blit((BITMAP*)main_pg[help].dat,screen,0,0,0,0,640,480);
      while(!key[KEY_ESC]);
      while(key[KEY_ESC]);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////void highscr()////////////////////////////////////////////////////////
void highscr()
{
    int y,cnt,te;
    char name[30],pont[]="00000";
    blit((BITMAP*)data[higscr].dat,screen,0,0,0,0,640,480);
    for(y=0;y<10;y++)
    {
        te=getpixel(hiscr,0,y);
        for(cnt=0;getpixel(hiscr,cnt+1,y)!=0;cnt++)
              name[cnt]=getpixel(hiscr,cnt+1,y);
        name[cnt]='\0';
        pont[4]=te%10+48;
        te/=10;
        pont[3]=te%10+48;
        te/=10;
        pont[2]=te%10+48;
        te/=10;
        pont[1]=te%10+48;
        te/=10;
        pont[0]=te%10+48;
        if(name[0]!='\0')
        {
                         textout_ex(screen,font,name,100,y*30+130,makecol(0,0,0),makecol(0,255,102));
                         textout_ex(screen,font,pont,450,y*30+130,makecol(0,0,0),makecol(0,255,102));             
        }
    }      
    readkey();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////void point_table()//////////////////////////////////////////
void point_table()
{
     int x,y,tcol,r,g,b;
     float per=0.2;
     for(y=0;y<768;y++)
     {
            for(x=0;x<1024;x++)
            {
                    tcol=getpixel(bmp,x,y);
                    r=getr(tcol)*per;
                    g=getg(tcol)*per;
                    b=getb(tcol)*per;
                    putpixel(bmp,x,y,makecol(r,g,b));         
            }                 
     }
     blit((BITMAP*)data[scrbrd].dat,bmp,0,0,192,144,256,192);
                         char str[]="00000";
                         int tee;
                         tee=points;
                         str[4]=tee%10+48;
                         tee/=10;
                         str[3]=tee%10+48;
                         tee/=10;
                         str[2]=tee%10+48;
                         tee/=10;
                         str[1]=tee%10+48;
                         tee/=10;
                         str[0]=tee+48;
                         textout_ex(bmp,font,str,290,250,makecol(0,0,0),makecol(102,204,255));    
     blit(bmp,screen,0,0,0,0,640,480);
     clear_keybuf();
     readkey();
     while(key[KEY_ENTER]);
     int i,pos,j;
     for(i=0,pos=-1;i<10;i++)
         if(getpixel(hiscr,0,i)<points)
         {     
               pos=i;
               break;
         }
     if(pos!=-1)
     {
         char name[30],pont[]="00000";
         int ctr=0,inc;
         blit((BITMAP*)data[higscr].dat,screen,0,0,0,0,640,480);
         for(i=0,inc=0;i+inc<10;i++)
         {
                if(i==pos)
                   inc=1;
                for(ctr=0;getpixel(hiscr,ctr+1,i)!=0;ctr++)
                          name[ctr]=getpixel(hiscr,ctr+1,i);
                name[ctr]='\0';
                tee=getpixel(hiscr,0,i);
                pont[4]=tee%10+48;
                tee/=10;
                pont[3]=tee%10+48;
                tee/=10;
                pont[2]=tee%10+48;
                tee/=10;
                pont[1]=tee%10+48;
                tee/=10;
                pont[0]=tee%10+48;
                if(name[0]!='\0')
                {
                         textout_ex(screen,font,name,100,(inc+i)*30+130,makecol(0,0,0),makecol(0,255,102));
                         textout_ex(screen,font,pont,450,(inc+i)*30+130,makecol(0,0,0),makecol(0,255,102));             
                }                
         }
         textout_ex(screen,font,str,450,pos*30+130,makecol(0,0,0),makecol(0,255,102));
         ctr=0;
         while(!key[KEY_ENTER])
         {
               name[ctr]=readkey();
              if(key[KEY_BACKSPACE])
               {  
                   name[ctr-1]=' ';
                   name[ctr]='\0';
                   textout_ex(screen,font,name,100,pos*30+130,makecol(0,0,0),makecol(0,255,102));                      
                   ctr--;
               }
               else  
                 ctr++;
               name[ctr]='\0';
               textout_ex(screen,font,name,100,pos*30+130,makecol(0,0,0),makecol(0,255,102));                      
         }  
         name[ctr-1]='\0';
         for(i=9;i>pos;i--)
         {
                putpixel(hiscr,0,i,getpixel(hiscr,0,i-1));           
                for(j=1;getpixel(hiscr,j,i-1)!=0;j++)
                    putpixel(hiscr,j,i,getpixel(hiscr,j,i-1));
                putpixel(hiscr,j,i,0);                  
                hline(hiscr,j+1,i,hiscr->w,0);
         }
         putpixel(hiscr,0,pos,points);
         for(i=0;name[i]!='\0';i++)
            putpixel(hiscr,i+1,pos,name[i]);          
     }
     highscr();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////void _credits()///////////////////////////////////////////////////
/* 
           Bitmap pointers to point to the credit images
*/
/*BITMAP *credee;
BITMAP *initia;
BITMAP *finall;

void _credits()
{
            int transcol=makecol(255,0,255);
            int _credxy[34]={   530,316,               //Specifies the placement of images
                                 36, 28,
                                349,320,
                                530, 28,
                                 20,324,
                                527,176,
                                158, 18,
                                238,318,
                                 16,179,
                                381, 10,
                                131,326,
                                389,176,
                                274, 16,
                                111,173,
                                297,167,
                                429,322,
                                214,174};
            int x,y,tcol1,tcol2,r,g,b,xco=clock(),yco=xco*xco,count=0;
            float per;
            initia=create_bitmap(100,150);
            finall=create_bitmap(640,480);
            clear_to_color(finall,makecol(255,255,255));
            clear_to_color(bmp,makecol(255,255,255));
            start:
            xco=_credxy[2*count];
            yco=_credxy[2*count+1];
            credee=(BITMAP*)credits[count].dat;
            stretch_blit(credee,initia,0,0,credee->w,credee->h,0,0,100,150);      
            for(per=0;per<=1;per+=0.005)
            { 
               blit(bmp,finall,0,0,0,0,640,480);
               for(y=0;y<initia->h;y++)
                   for(x=0;x<initia->w;x++)
                   {
                         tcol1=getpixel(initia,x,y);
                         if(tcol1!=transcol)
                         {
                             tcol2=getpixel(finall,x+xco,y+yco);
                             r=getr(tcol1)*per+getr(tcol2)*(1-per);
                             g=getg(tcol1)*per+getg(tcol2)*(1-per);
                             b=getb(tcol1)*per+getb(tcol2)*(1-per);
                             putpixel(bmp,x+xco,y+yco,makecol(r,g,b));                                     
                         }
                   }
               vsync();
               blit(bmp,screen,0,0,0,0,640,480);
            }
            blit(bmp,finall,0,0,0,0,640,480);
            count++;
            if(count<17)
            goto start;
            readkey();
               
}*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////int wannaqui()///////////////////////////////////////////
int wannaqui()
{
     int x,y,tcol,r,g,b;
     float per=0.2;
     for(y=0;y<768;y++)
     {
            for(x=0;x<1024;x++)
            {
                    tcol=getpixel(bmp,x,y);
                    r=getr(tcol)*per;
                    g=getg(tcol)*per;
                    b=getb(tcol)*per;
                    putpixel(bmp,x,y,makecol(r,g,b));         
            }                 
     }
     blit((BITMAP*)data[wannaquit].dat,bmp,0,0,192,144,256,192);
     blit((BITMAP*)data[yes1].dat,bmp,0,0,231,286,50,20);
     blit((BITMAP*)data[no1].dat,bmp,0,0,359,286,50,20);
     position_mouse(320,240);
     blit(bmp,screen,0,0,0,0,640,480);
     while(!key[KEY_ESC])
     { 
     			unscare_mouse();
                if(mouse_x>231&&mouse_x<281&&mouse_y>286&&mouse_y<306)
                { 
                       vsync();
                       scare_mouse();
                       blit((BITMAP*)data[yes2].dat,screen,0,0,228,284,55,23);
                       if (mouse_b & 1)
                           return 1;                               
                       unscare_mouse();
                }
                else
                if(mouse_x>359&&mouse_x<409&&mouse_y>286&&mouse_y<306)
                { 
                       vsync();
                       scare_mouse();
                       blit((BITMAP*)data[no2].dat,screen,0,0,356,284,55,23);
                       if (mouse_b & 1)
                           return 2;                               
                       unscare_mouse();
                }
                else
                {
                    vsync();
                    scare_mouse();
                    blit(bmp,screen,0,0,0,0,640,480);
                    unscare_mouse();
                }
     }
     return 2;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////main()/////////////////////////////////////////////////////
int main() 
{
	  init();
	  int t_level=1;
      bomber_man bom;
      enemy obj1;
      int choice,game_move;
      start:
      set_mouse_range(0,0,640,480);
      position_mouse(320,240);
      show_mouse(screen);
      scare_mouse();
      choice=main_page();
      scare_mouse();
      switch(choice)
      {
         case 1:
                    play_begin:
                    initialiser();
                    delay_man=-1;
                    man_status=0;
                    bom.level(t_level);
                    obj1.level(t_level);
                    ti2=clock();
                    while(1)
                    {
                            blit(backgrnd,bmp,0,0,0,0,640,480);
                            box_maker();
                            obj1.move();
                            game_move=bom.move();
                            if(game_move)
                            {
                                  t_level++;
                                  goto play_begin;         
                            }
                            while(ti1-ti2<30)
                            {
                                   if(key[KEY_ESC])
                                   break;
                                   ti1=clock();
                            }
                            ti2=ti1; 
                            vsync();
                            blit(bmp,screen,0,0,0,0,640,480);
                            if(man_status!=0&&delay_man==-1)
                                     delay_man=100;
                            if(delay_man!=-1)
                                     delay_man--;
                            if(delay_man==0)
                            {
                                  int ch;
                                  point_table();
                                  ch=ifman_dead();
                                  if(ch==1)
                                  {
                                        points=0;
                                        goto play_begin;
                                  }
                                  scare_mouse();
                                  clear_keybuf();
                                  break;               
                            }
                            if(key[KEY_ESC])
                            {        
                                     while(key[KEY_ESC]);
                                     if(wannaqui()==1)
                                     {   
                                         point_table();
                                         points=0;
                                         scare_mouse();
                                         break;
                                     }
                            }
                     }
                     while(key[KEY_ESC]);
                     goto start;
           case 2:
                highscr();
                while(key[KEY_ESC]);
                goto start;
           case 3:
                helper();
                while(key[KEY_ESC]);
                goto start;
           case 5:
                     break;
        }
        deinit();
	
        return 0;
}
END_OF_MAIN()
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////void init()/////////////////////////////////////////
void init() 
{
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	/*if (res != 0) 
    {
		allegro_message(allegro_error);
		exit(-1);
	}*/
	install_timer();
	install_keyboard();
	install_mouse();
	main_pg=load_datafile("openpg.dat");
	data=load_datafile("data.dat");
	//credits=load_datafile("crredits.dat");
    hiscr=load_bitmap("hiscr.bmp",NULL);
    if(hiscr==NULL)
    {
          hiscr=create_bitmap(50,10);
          clear_to_color(hiscr,0);               
    }
    tembmp=create_bitmap(640,480);         
    bmp=create_bitmap(640,480);
    box=(BITMAP*)data[boxa].dat;
    backgrnd=(BITMAP*)data[bk].dat;
    gateopen=(BITMAP*)data[gateopena].dat;
    gateclos=(BITMAP*)data[gateclosa].dat;
    blit((BITMAP*)data[bktem].dat,tembmp,0,0,0,0,640,480);
    noentry=getpixel(tembmp,0,0);
    man=getpixel(tembmp,1,0);
    bord=getpixel(tembmp,2,0);
    _box=getpixel(tembmp,3,0);
    __enemy=getpixel(tembmp,4,0);
    _blast=getpixel(tembmp,5,0);
    _bomb=getpixel(tembmp,6,0);
}
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////void deinit()///////////////////////////////////////////
void deinit() 
{
	clear_keybuf();
	unload_datafile(data);
	unload_datafile(main_pg);
	//unload_datafile(credits);
	save_bitmap("hiscr.bmp",hiscr,NULL);
	destroy_bitmap(hiscr);
}
/*****************************************THE END********************************************/
