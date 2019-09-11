void print(char *string)
{
    // Create a pointer to a char , and point it to the first text cell of
    // video memory (i.e. the top - left of the screen )
    for (char *video_memory = (char *)0xb8000; *string; video_memory += 2, string++)
    {
        // At the address pointed to by video_memory, store the character
        *video_memory = *string;
    }
}

void main()
{
    print("Hello World!");
}