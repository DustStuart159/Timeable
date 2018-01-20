#include"../header/CreatingTimeableLibrary.h"
extern char *s_pretreatLocalDir();

char *s_getRequestFile();
    char *s_showControllerMenu(DIR *Dp_Folder);
void v_showTimeable(char *sRF);

void v_observeTimeable() {
    char s_RF[100], s_SaveDay[15];
    /*------------------------------------------------------------------------------------------------------------------------------------------*/
    system("@cls||clear");

    strcpy(s_RF,s_getRequestFile());

    v_showTimeable(s_RF);
    /*------------------------------------------------------------------------------------------------------------------------------------------*/
    getch();
    return;
}
char *s_getRequestFile(){
    DIR *Dp_Folder;
    char s_SaveString[10];

    static char cp_Path[100];
    /*------------------------------------------------------------------------------------------------------------------------------------------*/
    for(strcpy(cp_Path,s_pretreatLocalDir());1;){
        printf("%s\n",cp_Path);
        Dp_Folder=opendir(cp_Path);

        if( Dp_Folder==NULL )
            break;

        strncat(&cp_Path[0],"/",1);
        strcpy(&s_SaveString[0],s_showControllerMenu(Dp_Folder));

        if( s_SaveString[3]!='.' )
            if(s_SaveString[0]!='D')
                strncat(cp_Path,s_SaveString,3);
            else
                strncat(cp_Path,s_SaveString,1);
        else
            strncat(cp_Path,s_SaveString,7);
    }
    /*------------------------------------------------------------------------------------------------------------------------------------------*/
    return &cp_Path[0];
}
char *s_showControllerMenu(DIR *Dp_Folder){
    int i_Controller=0;

    struct dirent *sDp_Ent;
    char s_Dir[10][10];
    /*-----------------------------------------------------------------------------------------------------------------------------------------*/
    system("@cls||clear");

    for(sDp_Ent=readdir(Dp_Folder);sDp_Ent!=NULL;sDp_Ent=readdir(Dp_Folder)){
            if( sDp_Ent->d_name[0]!='.' ){
                i_Controller=i_Controller+1;

                printf("%i. %s\n",i_Controller,sDp_Ent->d_name);
                strncpy(&s_Dir[i_Controller-1][0],sDp_Ent->d_name,(int)strlen(sDp_Ent->d_name));
            }
    }

    printf("Enter Number that you Want to Observe: ");
    i_Controller=getch() - '0';
    /*-----------------------------------------------------------------------------------------------------------------------------------------*/
    return &s_Dir[i_Controller-1][0];
}
void v_showTimeable(char *cRF){
    strTimeableTask sTTTask;

    FILE *FRequestFile=fopen(cRF,"r");
    system("@cls||clear");

    if(FRequestFile==NULL){
        printf("Timeable of Day isn't created. Let's creat!");

        return;
    }
    /*------------------------------------------------------------------------------------------------------------------------------------------*/
    printf("%s\t\t%s\t\t%s\n","Name of Task","Begin Time Point","End Time Point");

    for(fread(&sTTTask,sizeof(sTTTask),1,FRequestFile);!feof(FRequestFile);fread(&sTTTask,sizeof(sTTTask),1,FRequestFile))
        printf("%s\t\t%.2f\t\t%.2f\n",sTTTask.sNameTask,sTTTask.sTTTimeScope.fBegin,sTTTask.sTTTimeScope.fEnd);
    /*------------------------------------------------------------------------------------------------------------------------------------------*/
    fclose(FRequestFile);

    return;
}
