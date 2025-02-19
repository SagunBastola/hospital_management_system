    printf("\n enter your id:\t");
    scanf("%d", &d.docid);
    while (getchar() != '\n');  // Clear input buffer

    printf("\n Enter doctor name:\t");
    scanf("%[^\n]s", d.dname);
    while (getchar() != '\n');  // Clear input buffer
