/* 1. Keyword / Identifier */
#include <stdio.h>
#include <string.h>
int main(){
    FILE *f=fopen("input.txt","r");
    char s[100];
    char *kw[]={"int","float","char","double","if","else","for","while","return","void"};
    if(!f) return 1;
    while(fscanf(f,"%99s",s)==1){
        int k=0;
        for(int i=0;i<10;i++) if(!strcmp(s,kw[i])) k=1;
        if(k) printf("KEYWORD : %s\n",s);
        else printf("IDENTIFIER : %s\n",s);
    }
    fclose(f);
}

/* 2. Constant */
#include <stdio.h>
#include <ctype.h>
int main(){
    FILE *f=fopen("input.txt","r");
    char c,s[100];
    int i;
    if(!f) return 1;
    while((c=fgetc(f))!=EOF){
        if(isdigit(c)){
            i=0;
            do{s[i++]=c;c=fgetc(f);}while(isdigit(c));
            s[i]='\0';
            printf("CONSTANT : %s\n",s);
            if(c!=EOF) ungetc(c,f);
        }
    }
    fclose(f);
}

/* 3. Comments / Division */
#include <stdio.h>
int main(){
    FILE *f=fopen("input.txt","r");
    char c,n;
    if(!f) return 1;
    while((c=fgetc(f))!=EOF){
        if(c=='/'){
            n=fgetc(f);
            if(n=='/')
                while((c=fgetc(f))!=EOF&&c!='\n');
            else if(n=='*'){
                char p=0;
                while((c=fgetc(f))!=EOF){
                    if(p=='*'&&c=='/') break;
                    p=c;
                }
            }else{
                if(n!=EOF) ungetc(n,f);
                printf("DIVISION : /\n");
            }
        }
    }
    fclose(f);
}

/* 4. String */
#include <stdio.h>
int main(){
    FILE *f=fopen("input.txt","r");
    char c,s[100];
    int i;
    if(!f) return 1;
    while((c=fgetc(f))!=EOF){
        if(c=='"'){
            i=0;
            s[i++]=c;
            while((c=fgetc(f))!=EOF){
                s[i++]=c;
                if(c=='"') break;
            }
            s[i]='\0';
            printf("STRING : %s\n",s);
        }
    }
    fclose(f);
}

/* 5. Character */
#include <stdio.h>
int main(){
    FILE *f=fopen("input.txt","r");
    char c,a,b;
    if(!f) return 1;
    while((c=fgetc(f))!=EOF){
        if(c=='\''){
            a=fgetc(f);
            b=fgetc(f);
            if(b=='\'') printf("CHARACTER : '%c'\n",a);
        }
    }
    fclose(f);
}

/* 6. = < > ! Operators */
#include <stdio.h>
int main(){
    FILE *f=fopen("input.txt","r");
    char c,n;
    if(!f) return 1;
    while((c=fgetc(f))!=EOF){
        if(c=='='||c=='<'||c=='>'||c=='!'){
            n=fgetc(f);
            if(n=='=') printf("RELATIONAL : %c%c\n",c,n);
            else{
                if(n!=EOF) ungetc(n,f);
                if(c=='=') printf("ASSIGNMENT : =\n");
                else printf("RELATIONAL : %c\n",c);
            }
        }
    }
    fclose(f);
}

/* 7. + - * % Operators */
#include <stdio.h>
int main(){
    FILE *f=fopen("input.txt","r");
    char c,n;
    if(!f) return 1;
    while((c=fgetc(f))!=EOF){
        if(c=='+'||c=='-'||c=='*'||c=='%'){
            n=fgetc(f);
            if(n==c||n=='=') printf("ARITHMETIC : %c%c\n",c,n);
            else{
                if(n!=EOF) ungetc(n,f);
                printf("ARITHMETIC : %c\n",c);
            }
        }
    }
    fclose(f);
}

/* 8. && || Operators */
#include <stdio.h>
int main(){
    FILE *f=fopen("input.txt","r");
    char c,n;
    if(!f) return 1;
    while((c=fgetc(f))!=EOF){
        if(c=='&'||c=='|'){
            n=fgetc(f);
            if(n==c) printf("LOGICAL : %c%c\n",c,n);
            else{
                if(n!=EOF) ungetc(n,f);
                printf("INVALID OPERATOR : %c\n",c);
            }
        }
    }
    fclose(f);
}

/* 9. Separators / Invalid Symbols */
#include <stdio.h>
#include <string.h>
int main(){
    FILE *f=fopen("input.txt","r");
    char c;
    if(!f) return 1;
    while((c=fgetc(f))!=EOF){
        if(strchr("(){}[],;:",c)) printf("SEPARATOR : %c\n",c);
        else if(c!=' '&&c!='\n'&&c!='\t') printf("INVALID : %c\n",c);
    }
    fclose(f);
}
