//CANNON WARS!
#include<simplecpp>
#include<ctime>
#include<time.h>
#include<iostream>
#include<stdlib.h>
#include <stdio.h>
#include<time.h>
#include<string>
const double gravity=0.1;
const double pi=3.14159265;
const int shank=20;                                                                    // length of the shank of the Cannon
int point1=0,point2=0;                                                                 // Points of players
int cannon1x=90, cannon2x=690, cannon1y=0, cannon2y=0;                                 //Coordinates of center of Cannon
int check;                                                                             // Notify an explosion
int yA[20]= {40,80,160,130,190,80,45,150,200,100,140,60,90,100,30,0,110,180,75,50},
            cannon1_y[9]={80,160,130,190,80,45,150,200,100},
            cannon1_x[9]={40,80,120,160,200,240,280,320,360},
            cannon2_y[9]={140,60,90,100,30,0,110,180,75},
            cannon2_x[9]={400,440,480,520,560,600,640,680,720},
            yfinal[20];

int m_menu();

int rules()
{
    Rectangle background(400,300,800,600);    //clearing the screen
    background.setColor(LIGHTBLUE);
    background.setFill();

    settextstyle(10, HORIZ_DIR, 3);           // format of text
    Text rules(400,120,"Rules for Cannon War:");
    Text line1(400,160,"#1 Both the players have to fire upon each other.");
    Text line2(400,200,"#2 Points are awarded on the basis of accuracy of hit.");
    Text line3(400,240,"#3 The first person to reach a hundred points wins.");
    Text line4(400,280,"#4 Set the power and angle and click on fire.");
    Text line5(400,320,"#5 There is a random wind , a surprise element ;) ");
    Text line6(400,420,"Done By:");
    Text line7(400,450,"Leo Barros, Isaiah D'Costa, Duane Rodrigues,");
    Text line8(400,470,"Joshua Coutinho");

    Text backbutton(40,30,"BACK");           //go back to main menu
    Rectangle r(20,10,20,20);                //backbutton
    r.setColor(COLOR(0,0,0));
    r.setFill();

    int temp=getClick();
    int x = temp/65536;
    int y = temp%65536;

    if(x>10&&x<30&&y>0&&y<20)
        return 2;

}

int m_menu()
{
    Rectangle background(400,300,800,600);                // clear screen
    background.setColor(WHITE);
    background.setFill();

    setfillstyle(7, RED);

    floodfill(400,300,RED);

    settextstyle( 8, HORIZ_DIR, 4);           // format of text

    background.setColor(LIGHTBLUE);

    Rectangle R1(400,310,200,40);
    R1.setColor(COLOR(0,255,0));
    R1.setFill();
    Text t1(400,300,"New Game");
    t1.setColor(COLOR(255,0,0));

    Rectangle R2(400,410,200,40 );
    R2.setColor(COLOR(0,255,0));
    R2.setFill();
    Text t2(400,400,"Rules");
    t2.setColor(COLOR(255,0,0));            // BUTTONS ON MAIN MENU

    Rectangle R3(400,510,200,40);
    R3.setColor(COLOR(0,255,0));
    R3.setFill();
    Text t3(400,500,"Exit");
    t3.setColor(COLOR(255,0,0));

    Text t4(400,100,"Cannon WARS");
    t4.setColor(BLUE);

    TRY:    int temp = getClick();

    int x = temp / 65536 ;
    int y = temp % 65536 ;

    if (x>300&&x<600&&y>290&&y<330)
        return 1;

    else if (x>300&&x<600&&y>390&&y<430)
        return 2;

    else if (x>300&&x<600&&y>490&&y<530)
        closeCanvas();

    else goto TRY;                            // To counter invalid clicks

    wait(100);
}


void explosion(int x, int y)
{
    for (int i = 1; i<20 ; i+=1 )
    {
        Circle c(x,y,i);
        c.setColor(233);
        c.setFill(1);
        wait(0.05);
    }
    check=1;
}


class cannon
{
    public:

    Rectangle t;
    Circle c1,c2,c3,c4,c5,c6;                             //entities of the cannon
    Line l,l2,l3,l4;

    void check_can(int i, Circle c)
    {
        double distance;
        char hit;
        if(i%2==1)
        {
            distance = sqrt((c.getX()-cannon2x)*(c.getX()-cannon2x)+(c.getY()-cannon2y)*(c.getY()-cannon2y));       //calculating distance between cannon and projectile
        }

        else
        {
            distance = sqrt((c.getX()-cannon1x)*(c.getX()-cannon1x)+(c.getY()-cannon1y)*(c.getY()-cannon1y));
        }

        if(distance==0)
        {
            hit='f';
            explosion(c.getX(),c.getY());
            pointcalc(hit,i);                                     // function to calculate Cannon
        }
        else if(distance<20)
        {
            hit='p';
            explosion(c.getX(),c.getY());
            pointcalc(hit,i);
        }
    }

    void shot(double pow,double angle,int i,int wind)
    {
        //pow = (pow*4*sqrt(2))/100;                            // to optimise power
        //angle = (pi/180)*angle;                                 // to convert degree to radian measure
        // double vx = (pow*cos(angle))/10 , vy = -(pow*sin(angle))/10 , tf ;
        double vx = pow/15 + wind;
        double vy = -pow/8;

        int n=200;

        Circle c(l.getX(),l.getY(),7);
        c.setColor(BLACK);
        c.setFill(1);
        if(i%2==1)
        {
            repeat(n)
            {
                c.move(vx,vy);           //simulate projectile motion
                vy +=gravity;
                check_can(i,c);

                if(check>0)
                    break;
            }
        }
        else
        {
            repeat(n)
            {
                c.move(-vx,vy);
                vy +=gravity;
                check_can(i,c);

                if(check>0)
                    break;
            }
        }
    }

    void rotation (double angle , int i, int cannon_x, int cannon_y)                           //move the shank
    {
        l.reset(cannon_x,cannon_y,cannon_x+shank*cos(angle),cannon_y-5*sin(angle));

        l.reset(cannon_x,cannon_y,cannon_x+shank*cos(angle),cannon_y-shank*sin(angle));
        l2.reset(cannon_x+0.5,cannon_y-1,cannon_x+shank*cos(angle)+0.5,cannon_y-shank*sin(angle)-0.5);
        l3.reset(cannon_x+1,cannon_y-1,cannon_x+shank*cos(angle)+1,cannon_y-shank*sin(angle)-1);
        l4.reset(cannon_x+1.5,cannon_y-1.5,cannon_x+shank*cos(angle)+1.5,cannon_y-shank*sin(angle)-1.5);
    }

    void pointcalc(char hit , int i)
    {
        if(i%2==1)
        {
            if(hit=='f')                        //full hit or partial hit
                point1+=50;
            if(hit=='p')
                point1+=30;
        }

        if(i%2==0)
        {
            if(hit=='f')
                point2+=50;
            if(hit=='p')
                point2+=30;
        }
    }
};

void setscreen()
{
    cannon cannon1,cannon2;
    int RandIndex = rand() % 9; //generates a random number between 0 and 8

    cannon1.t.reset(cannon1_x[RandIndex],(490-(cannon1_y[RandIndex]/2)-5),30,10);
    cannon1.c1.reset(cannon1_x[RandIndex]-7,(500-(cannon1_y[RandIndex]/2)-5),5);
    cannon1.c3.reset(cannon1_x[RandIndex]+12.5,(490-(cannon1_y[RandIndex]/2)-5),5);
    cannon1.c2.reset(cannon1_x[RandIndex]+10,(500-(cannon1_y[RandIndex]/2)-5),5);
    RandIndex = rand() % 9; //generates a random number between 0 and 9

    cannon2.t.reset(cannon2_x[RandIndex],(490-(cannon2_y[RandIndex]/2)-5),30,10);
    cannon2.c4.reset(cannon2_x[RandIndex]-7,(500-(cannon2_y[RandIndex]/2)-5),5);
    cannon2.c6.reset(cannon2_x[RandIndex]-13.5,(490-(cannon2_y[RandIndex]/2)-5),5);
    cannon2.c5.reset(cannon2_x[RandIndex]+10,(500-(cannon2_y[RandIndex]/2)-5),5);

    cannon1.t.setColor(RED);                    //color of cannon1
    cannon1.t.setFill();

    cannon1.c1.setColor(BLACK);
    cannon1.c1.setFill();
    cannon1.c3.setColor(RED);
    cannon1.c3.setFill();
    cannon1.c2.setColor(BLACK);
    cannon1.c2.setFill();

    cannon2.t.setColor(BLUE);                   //color of canaon2
    cannon2.t.setFill();

    cannon2.c4.setColor(BLACK);
    cannon2.c4.setFill();
    cannon2.c6.setColor(BLUE);
    cannon2.c6.setFill();
    cannon2.c5.setColor(BLACK);
    cannon2.c5.setFill();

    cannon1x=cannon1.t.getX();
    cannon1y=cannon1.t.getY();
    cannon2x=cannon2.t.getX();
    cannon2y=cannon2.t.getY();

    int chance=1;
    double power,angle;
    settextstyle(10, HORIZ_DIR, 2);

    Text t1(80,10,"Power");
    Text t2(700,10,"Angle");
    Text t4(610,50,"0 deg");
    Text t5(760,50,"180 deg");
    Text t6(80,210,"Player 1");
    Text t7(720,210,"Player 2");

    Rectangle r1(80,30,100,20);         //power
    Rectangle r2(700,30,180,20);        //angle
    Rectangle r3(400,20,80,40);         //fire
    Rectangle r1o(80,30,100,20);        //outline of fire
    Rectangle r2o(700,30,180,20);       //outline of angle

    r1.setColor(BLUE);                  //color of power
    r1.setFill();

    r2.setColor(BLUE);                  //color of angle
    r2.setFill();

    r3.setColor(RED);                   //color of Fire
    r3.setFill();

    Text t3(400,20,"Fire");             //written here so that it overlaps the fill .

    int codx=0,cody=0,temp;
    temp=getClick();
    codx=temp/65536;
    cody=temp%65536;

    time_t now2 = time(0);
    char* dt = ctime(&now2);            // convert now to string form
    int wx=(int)dt;                     //converting dt to integer
    int wind=(wx%5)-2;                  //random wind

    LABEL :check=0;
    cout<<"Player 1: "<<point1<<" points"<<endl;           //consoling out points
    cout<<"Player 2: "<<point2<<" points"<<endl;

    std::string s1 = "Player 1: ";
    char numstr[21];
    sprintf(numstr, "%d", point1);
    s1 = s1 + numstr;
    Text p1(700,120,s1);
    std::string s2 = "Player 2: ";
    sprintf(numstr, "%d", point2);
    s2 = s2 + numstr;
    Text p2(700,140,s2);
    while(true)
    {
        if(point1>=100)
        {
            Text w1(400,300,"Cannon 1 is the winner");
            wait(100);
        }

        if(point2>=100)
        {
            Text w2(400,300,"Cannon 2 is the winner");
            wait(100);
        }

        temp = getClick();
        codx=temp/65536;
        cody=temp%65536;
        if(codx>30&&codx<130&&cody>20&&cody<40)
        {
            r1.reset((30+codx)/2,30,codx-30,20);            //adjust power
            power = codx-30;
        }

        if(codx>610&&codx<790&&cody>20&&cody<40)
        {

            r2.reset((610+codx)/2,30,codx-610,20);
            angle = (codx-610);
            if(chance%2==1)
            {
                //initialize the random seed
                cannon1.rotation((angle*pi)/180,chance,cannon1.t.getX(),cannon1.t.getY());
            }

            else
            {
                //initialize the random seed
                cannon2.rotation(((180*pi)/180)-((angle*pi)/180),chance,cannon2.t.getX(),cannon2.t.getY());
            }
        }

        if(codx>360&&codx<440&&cody<40&&cody>0)
        {
            if(point2<100&&point1<100)
            {
                if(chance%2==1)
                {
                    cannon1.shot(power,angle,chance,wind);
                    int RandIndex = rand() % 9; //generates a random number between 0 and 9

                    cannon1.t.reset(cannon1_x[RandIndex],(490-(cannon1_y[RandIndex]/2)-5),30,10); //to randomize position of cannons on terrain after each shot
                    cannon1.c1.reset(cannon1_x[RandIndex]-7,(500-(cannon1_y[RandIndex]/2)-5),5);
                    cannon1.c3.reset(cannon1_x[RandIndex]+12.5,(490-(cannon1_y[RandIndex]/2)-5),5);
                    cannon1.c2.reset(cannon1_x[RandIndex]+10,(500-(cannon1_y[RandIndex]/2)-5),5);
                    cannon1.rotation((45*pi)/180,chance,cannon1.t.getX(),cannon1.t.getY());
                    cannon1x=cannon1.t.getX();
                    cannon1y=cannon1.t.getY();
                        //calling SHOT
                }
                else
                {
                    cannon2.shot(power,angle,chance,wind);
                    int RandIndex = rand() % 9; //generates a random number between 0 and 9

                    cannon2.t.reset(cannon2_x[RandIndex],(490-(cannon2_y[RandIndex]/2)-5),30,10);
                    cannon2.c4.reset(cannon2_x[RandIndex]-7,(500-(cannon2_y[RandIndex]/2)-5),5);
                    cannon2.c6.reset(cannon2_x[RandIndex]-13.5,(490-(cannon2_y[RandIndex]/2)-5),5);
                    cannon2.c5.reset(cannon2_x[RandIndex]+10,(500-(cannon2_y[RandIndex]/2)-5),5);
                    cannon2.rotation(((180*pi)/180)-((45*pi)/180),chance,cannon2.t.getX(),cannon2.t.getY());
                    cannon2x=cannon2.t.getX();
                    cannon2y=cannon2.t.getY();
                        //calling SHOT
                }
            }
            chance+=1;
            goto LABEL;
        }
    }
}


int main()
{
   initCanvas("CANNON WARS",800,600);
   int temp = m_menu();

    if (temp==2)
    {
        temp=rules();
        if(temp==1)
        {
            m_menu();
        }
    }

    if(temp==1)
    {
        Rectangle background(400,300,800,600);    //clearing the screen
        background.setColor(LIGHTBLUE);
        background.setFill();
        Rectangle T[20];
        Rectangle R(400,550,800,100);
        R.setColor(GREEN);
        R.setFill();
        {
            for(int i=0;i<20;i++)
            {
                yfinal[i]=yA[i];
                T[i].reset(i*40,500,40,yA[i]);
                T[i].setColor(GREEN);
                T[i].setFill();
            }
        }
        setscreen();
    }
}
