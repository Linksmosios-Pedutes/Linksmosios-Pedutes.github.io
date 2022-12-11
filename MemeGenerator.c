#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    FILE *inFile;
    inFile = fopen("meme_input.txt", "r");

    // username
    char username[1024];
    fgets(username, 1024, inFile);
    username[strcspn(username, "\n")] = 0;  // removes newline char from usesname

    // title
    char title[1024];
    fgets(title, 1024, inFile);
    title[strcspn(title, "\n")] = 0;  // removes newline char from title

    // image
    char image[1024];
    fgets(image, 1024, inFile);
    image[strcspn(image, "\n")] = 0;  // removes newline char from image name

    // width
    char width[1024];
    fgets(width, 1024, inFile);
    width[strcspn(width, "\n")] = 0;  // removes newline char from width

    // height
    char height[1024];
    fgets(height, 1024, inFile);
    height[strcspn(height, "\n")] = 0;  // removes newline char from height

    fclose(inFile);

    FILE *htmlFile, *phFile, *endFile;
    htmlFile = fopen("Memes.html", "r");
    phFile = fopen("PlaceHolder.html", "w");

    char c = fgetc(htmlFile);
    while(c != '@')
    {
        putc(c, phFile);
        c = fgetc(htmlFile);
    }
    putc('$',phFile);
    for(int i = 0; i < 4; ++i){
        c = fgetc(htmlFile);        // Finishes scanning this separator line: <!--@--> and replaces the @ with $
        putc(c, phFile);
    }
    fclose(htmlFile);
    fclose(phFile);
    
    //removes the old html file
    remove("Memes.html");
    //renames the file PlaceHolder to original name
    rename("PlaceHolder.html", "Memes.html");

    htmlFile = fopen("Memes.html", "a");
    endFile = fopen("end.txt", "r");

    // date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[24];
    sprintf(date, "%s", asctime(tm));
    date[strcspn(date, "\n")] = 0;  // removes newline char from date
    
    fprintf(htmlFile, "<div class=\"blog\"> <div class=\"username_date_line\"> <div class=\"username\"> %s </div><div class=\"dot\"> &#x2022 </div><div class=\"date\"> %s </div><p class=\"blog-line\"></p></div><div> <p class=\"blog-title\"> %s </p></div><div> <img src=\"%s\" width=\"%s\" height=\"%s\"></div></div><!--@-->\n", username, date, title, image, width, height);
    
    // prints the end brackets of code
    c = fgetc(endFile);
    while (c != EOF){
        fputc(c,htmlFile);
        c = fgetc(endFile);
    }
    
    fclose(endFile);
    fclose(htmlFile);

    return 0;
}
