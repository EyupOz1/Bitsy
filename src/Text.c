#include "Text.h"
/*
Text TextInput(char* text, float x, float y, float width, float height)
{
    return (Text){
        .text = text
        .letterCount = 0,
        .isVisible = 1,
        .pos = (Rectangle){.x = x, .y = y, .width = width, .height = height}};
}

void Text_collision(Text *text)
{

        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = GetCharPressed();
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (text->letterCount < 20))
            {
                text->name[text->letterCount] = (char)key;
                text->name[text->letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                text->letterCount++;
            }

            key = GetCharPressed(); // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            text->letterCount--;
            if (text->letterCount < 0)
                text->letterCount = 0;
            text->name[text->letterCount] = '\0';
        }
    }

}

void Text_draw(Text *text)
{

    DrawRectangleRec(text->textBox, (Color){200, 200, 200, 50});
    if (text->mouseOnText)
        DrawRectangleLines((int)text->textBox.x, (int)text->textBox.y, (int)text->textBox.width, (int)text->textBox.height, RED);
    else
        DrawRectangleLines((int)text->textBox.x, (int)text->textBox.y, (int)text->textBox.width, (int)text->textBox.height, DARKGRAY);

    DrawText(text->name, (int)text->textBox.x + 5, (int)text->textBox.y + 8, 40, MAROON);
}*/