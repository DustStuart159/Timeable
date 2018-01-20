#include"../header/CreatingTimeableLibrary.h"
#include<stdlib.h>

extern char *s_getCurrentTime();
extern char *s_pretreatLocalDir();

char sMotherFile[100];
int const iMax=20;
int const iTrick=19;

void *v_creatFile(char *sCreateLocation,char *sFileName);
    void v_addTasks(char *sFileName,FILE *FFile);
        int i_addTaskArray(strTimeableTask *sTTTA,int iTL);
            void v_arrangeTasks(strTimeableTask *sTTTasksArray,int iEleNum);

void v_creatTimeable(){
    char sCurrentTime[100], sLocationFile[100], sFileName[4];
    strcpy(sCurrentTime,""); strcpy(sLocationFile,""); strcpy(sFileName,"");
/*------------------------------------------------------------------------------------------------------------------------------------------*/
    strcpy(sLocationFile,s_pretreatLocalDir());
    for( strcpy(sCurrentTime,s_getCurrentTime()); strcmp(sCurrentTime,"")!=0; strcpy(sCurrentTime,&sCurrentTime[3]) ){
        strncpy(sFileName,sCurrentTime,3);
        v_creatFile(sLocationFile,&sFileName[0]);
    }
/*------------------------------------------------------------------------------------------------------------------------------------------*/
    system("@cls||clear");
    printf("CREATED Timeable FOR TODAY");
    getch();
    return;
}


void *v_creatFile(char *sCreateLocation,char *sFileName){
    FILE *FFile;
    char sResult[100];
    strcpy(sResult,"");
    sFileName[3]='\0';
/*----------------------------------------------------------------------------------------------------------------------------*/
    strcpy(sResult,sCreateLocation); strcat(sResult,"/");
    if( sFileName[0]!='D' )
        strncat(sResult,sFileName,3);
    else
        strcat(sResult,"D");
    if( !opendir(sResult) )
        mkdir(sResult);
    strcpy(sCreateLocation,sResult);

    strncat(sResult,"/",1); strncat(sResult,sFileName,3); strncat(sResult,".txt",4);
    if( !fopen(sResult,"r") ){
        FFile=fopen(sResult,"w");
        v_addTasks(sFileName, FFile);
        fclose(FFile);
    }

    strcpy(sMotherFile,sResult);
/*------------------------------------------------------------------------------------------------------------------------------*/
    return;
}
void v_addTasks(char *sFileName,FILE *FFile){
    strTimeableTask sTTTasks[iMax], sTTSaveTask;
    int i, iCout, iTaskAmount; float fTimePoint;
    char s_Number[3];

    FILE *FMotherFile=fopen(sMotherFile,"r");
//------------------------------------------------------------------------------------------------//
    if(sFileName[0]!='D'){
        switch(sFileName[0]){
        case 'Q':
            iTaskAmount=3;
            break;
        case 'W':
            iTaskAmount=6;
            break;
        default:
            iTaskAmount=4;
            break;
        }

        if(sFileName[0]=='Y'){
            printf("Enter %i Jobs that you need to do in %s:\n",iTaskAmount,sFileName);
            iCout=i_addTaskArray(sTTTasks,iTaskAmount);
            for(i=0;i<iCout;i++)
                fwrite(&sTTTasks[i], sizeof(sTTTasks[i]), 1, FFile);
        } else{
            FMotherFile=fopen(sMotherFile,"r");
            for(i=0;i<sFileName[2]-'0';i++)
                fread(&sTTSaveTask,sizeof(sTTSaveTask),1,FMotherFile);
            fclose(FMotherFile);

            printf("Enter %i Jobs that links with %s in %s:\n",iTaskAmount,sTTSaveTask.sNameTask,sFileName);
            iCout=i_addTaskArray(sTTTasks,iTaskAmount);
            for(i=0;i<iCout;i++)
                fwrite(&sTTTasks[i], sizeof(sTTTasks[i]), 1, FFile);
        }
    }else{
        FMotherFile=fopen(sMotherFile,"r");
        for(fread(&sTTSaveTask,sizeof(sTTSaveTask),1,FMotherFile);1;fread(&sTTSaveTask,sizeof(sTTSaveTask),1,FMotherFile)){
            sprintf(&s_Number[0],"%i",(int)sTTSaveTask.sTTTimeScope.fEnd);

            if( strlen(&s_Number[0])==1 ){
                s_Number[1]=s_Number[0];
                s_Number[0]='0';
            }

            if( strncmp(&sFileName[1],&s_Number[0],2)==0 )
                break;
        }
        fclose(FMotherFile);
        printf("Enter Tasks that links with %s in %s:\n",sTTSaveTask.sNameTask,sFileName);

        printf("Enter Tasks that you have to do in %s:\n",sFileName);
        iCout=i_addTaskArray(sTTTasks,iMax);

        printf("Enter Tasks that you need to do in %s:\n",sFileName);
        iCout=i_addTaskArray(sTTTasks,iTrick);

        for(i=0;i<iCout;i++)
            fwrite(&sTTTasks[i], sizeof(sTTTasks[i]), 1, FFile);
    }
//-------------------------------------------------------------------------------//
    return;
}

int i_addTaskArray(strTimeableTask *sTTTA,int iTL){
    int iReturnValue=0, iRemain=0,
        i, j;
    float fTimeScope=0;
/*-----------------------------------------------------------------------------------------------------------------------------------------*/
    if(iTL!=iTrick)
        for(i=0;i<iTL;i++){
            printf("Let's enter Task that You are going to Do:\n");
            fflush(stdin);
            if( strcmp(gets(sTTTA[i].sNameTask),"")==0 )
                break;

            iReturnValue++;

            if(iTL==iMax){
                printf("Enter Start time point: ");
                fflush(stdin); scanf("%f",&sTTTA[i].sTTTimeScope.fBegin);
            }
            else
                sTTTA[i].sTTTimeScope.fBegin=0;

            printf("Enter End time point: ");
            fflush(stdin); scanf("%f",&sTTTA[i].sTTTimeScope.fEnd);
            v_arrangeTasks(sTTTA,iReturnValue);
        }
    else{
        iReturnValue=0;
        for(i=0;strcmp(sTTTA[i].sNameTask,"")!=0;i++)
            iReturnValue++;
        for(i=iReturnValue;i<iMax;i++){
            if(i_addTaskArray(&sTTTA[i],1)==0)
                break;
            fTimeScope=sTTTA[i].sTTTimeScope.fEnd-sTTTA[i].sTTTimeScope.fBegin;
            for(j=1;j<iReturnValue;j++)
                if( fTimeScope<=(sTTTA[j].sTTTimeScope.fBegin-sTTTA[j-1].sTTTimeScope.fEnd) ){
                    sTTTA[i].sTTTimeScope.fBegin=sTTTA[j-1].sTTTimeScope.fEnd;
                    sTTTA[i].sTTTimeScope.fEnd=sTTTA[i].sTTTimeScope.fBegin+fTimeScope;
                    iReturnValue++;
                    v_arrangeTasks(sTTTA,iReturnValue);
                    break;
                }
            if( j==iReturnValue ){
                    iRemain++; i--;
                    sTTTA[iMax-iRemain]=sTTTA[i+1];
                }
            }
            printf("Tasks aren't Done:\n");
            for(i=0;i<iRemain;i++)
                printf("\t%s\n",sTTTA[iMax-i-1].sNameTask);
            getch();
        }
/*-----------------------------------------------------------------------------------------------------------------------------------------*/
    return iReturnValue;
}
void v_arrangeTasks(strTimeableTask *sTTTasksArray,int iEleNum){
    int i,j;
    strTimeableTask sTTSave;
/*------------------------------------------------------------------------------------------------------------------------------------------*/
    for(i=0;i<iEleNum;i++)
        for(j=i;j<iEleNum;j++)
            if(sTTTasksArray[i].sTTTimeScope.fEnd>sTTTasksArray[j].sTTTimeScope.fEnd){
                sTTSave=sTTTasksArray[i];
                sTTTasksArray[i]=sTTTasksArray[j];
                sTTTasksArray[j]=sTTSave;
            }
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
    return;
}
