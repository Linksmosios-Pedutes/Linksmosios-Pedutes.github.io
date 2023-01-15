#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    FILE *inFile;
    inFile = fopen("input.txt", "r");

    // username
    char username[1024];
    fgets(username, 1024, inFile);
    username[strcspn(username, "\n")] = 0;  // removes newline char from usesname

    // title
    char title[1024];
    fgets(title, 1024, inFile);
    title[strcspn(title, "\n")] = 0;  // removes newline char from title

    // text
    char *text_ptr = NULL;
    int c_n = 1; // char count
    char tc = fgetc(inFile);
    while (tc != EOF) {
        text_ptr = (char *)realloc(text_ptr, c_n * sizeof(char));
        text_ptr[c_n - 1] = tc;
        ++c_n;
        tc = fgetc(inFile);
    }
    text_ptr[c_n - 1] = '\0';
    fclose(inFile);

    FILE *htmlFile, *pt1File, *pt2File;
    htmlFile = fopen("website.html", "w");
    pt1File = fopen("part1.txt", "r");
    pt2File = fopen("part2.txt", "r");

    // date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[24];
    sprintf(date, "%s", asctime(tm));
    date[strcspn(date, "\n")] = 0;  // removes newline char from date

    // prints 1st part of code
    char c = fgetc(pt1File);
    while (c != EOF) {
        fputc(c,htmlFile);
        c = fgetc(pt1File);
    }
    
    fprintf(htmlFile, "<div class=\"blog\"> <div class=\"username_date_line\"> <div class=\"username\"> %s </div><div class=\"dot\"> &#x2022 </div><div class=\"date\"> %s </div><p class=\"blog-line\"></p></div><div> <p class=\"blog-title\"> %s </p></div><div> <p class=\"text\"> %s </p></div></div>", username, date, title, text_ptr);
    
    free(text_ptr);
    
    // prints 2nd part of code
    c = fgetc(pt2File);
    while (c != EOF){
        fputc(c,htmlFile);
        c = fgetc(pt2File);
    }
    
    fclose(pt2File);
    fclose(htmlFile);
    
    htmlFile = fopen("website.html", "r");
    
    //scans html file until reaches separator
    while(c != '@'){
        c = fgetc(htmlFile);
    }
    for(int i = 0; i < 4; ++i){
        c = fgetc(htmlFile);        // Finishes scanning this separator line: <!--@-->
    }
    
    // saves new and old blog posts
    pt2File = fopen("part2.txt", "w");
    while(c != EOF)
    {
        fputc(c, pt2File);
        c = fgetc(htmlFile);
    }

    fclose(pt1File);
    fclose(pt2File);
    fclose(htmlFile);
    return 0;
}
