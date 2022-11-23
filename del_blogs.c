#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *delFile, *pt2File, *htmlFile;
    delFile = fopen("part1.txt", "r");
    pt2File = fopen("part2.txt", "w");
    htmlFile = fopen("blog.html", "w");

    char c = fgetc(delFile);
    while (c != EOF) {
        fputc(c, htmlFile);
        c = fgetc(delFile);
    }
    fprintf(pt2File, "</div></div></div></body></html>");
    fprintf(htmlFile, "</div></div></div></body></html>");
    fclose(pt2File);
    fclose(htmlFile);
    fclose(delFile);
    return 0;
}