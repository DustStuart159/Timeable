#include"header/CreatingTimeableLibrary.h"
char *s_getCurrentTime();
char *s_pretreatLocalDir();

extern int i_showMainMenu();
extern void v_creatTimeable();
extern void v_observeTimeable();

int main(){
    char cController=s_getCurrentTime()[11];
    int iController;

    if(cController=='5')
        printf("Sorry, App don't run in this day!");
    else
        for(iController=i_showMainMenu();(iController>0)&&(iController<5);iController=i_showMainMenu())
            switch(iController){
            case 1:
                v_creatTimeable();
                break;
            case 2:
                v_observeTimeable(1);
                break;
            default:
                break;
            }

    return 0;
}
char *s_getCurrentTime(){
    time_t rawtime;
    static char cSaveDate[100];
    char cSource[25], cDestination[25];

    {
        strcpy(cSaveDate,"");

        time (&rawtime);
        strcpy(cSource,ctime(&rawtime)); //"Fri Dec 22 15:26:14 2017"
        cSource[24]='\0';

        strcpy(cDestination,"");
    }
    {
        strcat(cSaveDate,"Y");
        strcpy(cDestination,&cSource[strlen(cSource)-2]);
        strcat(cSaveDate,cDestination);
    }
    {
        strcat(cSaveDate,"Q");
        strncpy(cDestination,&cSource[4],3);
        cDestination[3]='\0';
        if( strcmp(cDestination,"Jan")==0
           || strcmp(cDestination,"Feb")==0
           || strcmp(cDestination,"Mar")==0 )
            strcat(cSaveDate,"01");
        else if( strcmp(cDestination,"Apr")==0
           || strcmp(cDestination,"May")==0
           || strcmp(cDestination,"Jun")==0 )
            strcat(cSaveDate,"02");
        else if( strcmp(cDestination,"Jul")==0
           || strcmp(cDestination,"Aug")==0
           || strcmp(cDestination,"Sep")==0 )
            strcat(cSaveDate,"03");
        else if( strcmp(cDestination,"Oct")==0
           || strcmp(cDestination,"Nov")==0
           || strcmp(cDestination,"Dec")==0 )
            strcat(cSaveDate,"04");
    }
    {
        strcat(cSaveDate,"M");
        if(strcmp(cDestination,"Jan")==0)
            strcpy(cDestination,"01");
        if(strcmp(cDestination,"Feb")==0)
            strcpy(cDestination,"02");
        if(strcmp(cDestination,"Mar")==0)
            strcpy(cDestination,"03");
        if(strcmp(cDestination,"Apr")==0)
            strcpy(cDestination,"04");
        if(strcmp(cDestination,"May")==0)
            strcpy(cDestination,"05");
        if(strcmp(cDestination,"Jun")==0)
            strcpy(cDestination,"06");
        if(strcmp(cDestination,"Jul")==0)
            strcpy(cDestination,"07");
        if(strcmp(cDestination,"Aug")==0)
            strcpy(cDestination,"08");
        if(strcmp(cDestination,"Sep")==0)
            strcpy(cDestination,"09");
        if(strcmp(cDestination,"Oct")==0)
            strcpy(cDestination,"10");
        if(strcmp(cDestination,"Nov")==0)
            strcpy(cDestination,"11");
        if(strcmp(cDestination,"Dec")==0)
            strcpy(cDestination,"12");
        strcat(cSaveDate,cDestination);
    }
    {
        int i;
        strcat(cSaveDate,"W");
        strncpy(cDestination,&cSource[strlen(cSource)-16],2);
        i=atoi(cDestination);

        switch(i/7){
        case 0:
            strcat(cSaveDate,"01");
            break;
        case 1:
            if(i%7==0)
                strcat(cSaveDate,"01");
            else
                strcat(cSaveDate,"02");
            break;
        case 2:
            if(i%7==0)
                strcat(cSaveDate,"02");
            else
                strcat(cSaveDate,"03");
            break;
        case 3:
            if(i%7==0)
                strcat(cSaveDate,"03");
            else
                strcat(cSaveDate,"04");
            break;
        case 4:
            if(i%7==0)
                strcat(cSaveDate,"04");
            else
                strcat(cSaveDate,"05");
            break;
        default:
            break;
        }
    }
    {
        strcat(cSaveDate,"D");
        strcat(cSaveDate,cDestination);
    }

    return &cSaveDate[0];
}
char *s_pretreatLocalDir(){
    int i;
    static char sLocalDir[100];
    /*-----------------------------------------------------------------------------------------------------------------------------------------*/
    getcwd(sLocalDir, sizeof(sLocalDir));
    for(i=0;i<strlen(sLocalDir);i++)
    if(sLocalDir[i]=='\\')
        sLocalDir[i]='/';

    strncat(&sLocalDir[0],"/Data",5);

    if( opendir(&sLocalDir[0])==NULL )
        mkdir(sLocalDir);
    /*-----------------------------------------------------------------------------------------------------------------------------------------*/
    return sLocalDir;
}
