#include<stdio.h>
int pad[100][100];
int nowplayer;
void get(void);
bool down(int X,int Y);
bool win(int noW);
void splayer(void);
int main()
{
    nowplayer=1;
    for(int i=0;i<20;i++)
    {
        for(int ii=0;ii<20;ii++)
        {
            printf("%d,%d-set\n",i,ii);
            pad[ii][i]=0;
        }
    }
    for(int i=0;i<20;i++)
    {
        for(int ii=0;ii<20;ii++)
        {
            printf("%d,%d-set\n",i,ii);
            pad[ii][i]=0;
        }
    }
    int a,b;
    get();
    for(;;)
    {
        scanf("%d,%d",&a,&b);
    if(down(a-1,b-1))
    {
        if(win(nowplayer))
        break;
        else
        splayer();
        get();
    }
    else
    printf("can't do it!\n");
    }
    printf("game over\n");
}
void get(void)
{
    char padw[1000000]={"player:"};
    int k=0;
    padw[k]=nowplayer+48;
    k++;
    for(int i=0;i<50;i++)
    {
    padw[k]=' ';
    k++;    
    }
    padw[k]='\n';
    k++;
    padw[k]=' ';
    k++;
    padw[k]=' ';
    k++;
    for(int ii=0;ii<20;ii++)
    {
        padw[k]='|';
        k++;
        padw[k]=(ii+1)/10+48;
        k++;
        padw[k]=(ii+1)%10+48;
        k++;
    }
    padw[k]='\n';
    k++;
    for(int i=0;i<20;i++)
    {
        padw[k]=(i+1)/10+48;
        k++;
        padw[k]=(i+1)%10+48;
        k++;
        for(int ii=0;ii<20;ii++)
        {
            padw[k]='|';
            k++;
            if(pad[i][ii]==1)
            padw[k]='o';
            else if(pad[i][ii]==2)
            padw[k]='x';
            else
            padw[k]='#';
            k++;
            padw[k]=' ';
            k++;
        }
        padw[k]='\n';
        k++;
    }
    printf("%s\n",padw);
}
bool down(int x,int y)
{
    if(x>20||x<0||y>20||y<0)
    return false;
    if(pad[x][y]==0)
    {
        pad[x][y]=nowplayer;
        return true;
    }
    else
    {
        return false;
    }
}
bool win(int np)
{
    for(int x=0;x<20;x++)
    {
            for(int y=0;y<20;y++)
            {
            //printf("%d,%d|tested to %d\n",x,y,np);
                if(pad[x][y]==np)
                    if(pad[x+1][y]==np)
                        if(pad[x+2][y]==np)
                            if(pad[x+3][y]==np)
                                if(pad[x+4][y]==np)
                                {
                                    //printf("a1,tested");
                                    return true;
                                }

                if(pad[x][y]==np)
                    if(pad[x][y+1]==np)
                        if(pad[x][y+2]==np)
                            if(pad[x][y+3]==np)
                                if(pad[x][y+4]==np)
                                    {
                                //  printf("a2,tested");
                                    return true;
                                    }
                if(pad[x+4][y+4]==np)
                    if(pad[x+3][y+3]==np)
                        if(pad[x+2][y+2]==np)
                            if(pad[x+1][y+1]==np)
                                if(pad[x][y]==np)
                                    {
                                    //printf("a3,tested");
                                    return true;
                                    }
                if(pad[x][y+4]==np)
                    if(pad[x+1][y+3]==np)
                        if(pad[x+2][y+2]==np)
                            if(pad[x+3][y+1]==np)
                                if(pad[x+4][y]==np)
                                    {
                                    //printf("a4,tested");
                                    return true;
                                    }
        }
    }
    return false;
}
void splayer(void)
{
    if(nowplayer==1)
            nowplayer=2;
        else 
            nowplayer=1;
    return;
}
