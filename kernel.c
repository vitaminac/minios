void main()
{
    // Create a pointer to a char , and point it to the first text cell of
    // video memory (i.e. the top - left of the screen )
    char *video_memory = (char *)0xb8000;
    // At the address pointed to by video_memory , store the character ’X’
    // (i.e. display ’X’ in the top - left of the screen ).
    *video_memory = 'H';
    video_memory += 2;
    *video_memory = 'e';
    video_memory += 2;
    *video_memory = 'l';
    video_memory += 2;
    *video_memory = 'l';
    video_memory += 2;
    *video_memory = 'o';
}