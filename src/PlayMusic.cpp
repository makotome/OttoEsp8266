#include "PlayMusic.h"

void PlayMusic::happyNewYear(Otto *ottox)
{
    // 新年好呀，新年好呀，祝贺大家新年好！
    // 旋律简谱：1 1 3 1 | 5 3 2 - | 1 1 3 1 | 5 3 2 - |
    //          5 5 6 5 | 4 3 1 - | 1 1 2 3 | 1 2 - - |
    //          1 1 2 3 | 5 4 - - | 5 5 6 5 | 4 3 1 - |

    // 第一段：新年好呀，新年好呀
    ottox->_tone(note_G4, 400, 100); // 1
    ottox->_tone(note_G4, 400, 100); // 1
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_G4, 400, 100); // 1
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_A4, 800, 200); // 2 -

    // 第二段：新年好呀，新年好呀
    ottox->_tone(note_G4, 400, 100); // 1
    ottox->_tone(note_G4, 400, 100); // 1
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_G4, 400, 100); // 1
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_A4, 800, 200); // 2 -

    // 第三段：祝贺大家新年好
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_E5, 400, 100); // 6
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_C5, 400, 100); // 4
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_G4, 800, 200); // 1 -

    // 第四段：我们唱歌
    ottox->_tone(note_G4, 400, 100); // 1
    ottox->_tone(note_G4, 400, 100); // 1
    ottox->_tone(note_A4, 400, 100); // 2
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_G4, 400, 100); // 1
    ottox->_tone(note_A4, 800, 200); // 2 -

    // 第五段：我们跳舞
    ottox->_tone(note_G4, 400, 100); // 1
    ottox->_tone(note_G4, 400, 100); // 1
    ottox->_tone(note_A4, 400, 100); // 2
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_C5, 800, 200); // 4 -

    // 第六段：祝贺大家新年好
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_E5, 400, 100); // 6
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_C5, 400, 100); // 4
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_G4, 800, 200); // 1 -
}

// star
void PlayMusic::twinkleStar(Otto *ottox)
{
    // 1 1 5 5 6 6 5 -
    ottox->_tone(note_G4, 400, 100); // 1
    ottox->_tone(note_G4, 400, 100); // 1
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_E5, 400, 100); // 6
    ottox->_tone(note_E5, 400, 100); // 6
    ottox->_tone(note_D5, 800, 200); // 5

    // 4 4 3 3 2 2 1 -
    ottox->_tone(note_C5, 400, 100); // 4
    ottox->_tone(note_C5, 400, 100); // 4
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_A4, 400, 100); // 2
    ottox->_tone(note_A4, 400, 100); // 2
    ottox->_tone(note_G4, 800, 200); // 1

    // 5 5 4 4 3 3 2 -
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_C5, 400, 100); // 4
    ottox->_tone(note_C5, 400, 100); // 4
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_A4, 800, 200); // 2

    // 5 5 4 4 3 3 2 -
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_C5, 400, 100); // 4
    ottox->_tone(note_C5, 400, 100); // 4
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_A4, 800, 200); // 2

    // 1 1 5 5 6 6 5 -
    ottox->_tone(note_G4, 400, 100); // 1
    ottox->_tone(note_G4, 400, 100); // 1
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_D5, 400, 100); // 5
    ottox->_tone(note_E5, 400, 100); // 6
    ottox->_tone(note_E5, 400, 100); // 6
    ottox->_tone(note_D5, 800, 200); // 5

    // 4 4 3 3 2 2 1 -
    ottox->_tone(note_C5, 400, 100); // 4
    ottox->_tone(note_C5, 400, 100); // 4
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_B4, 400, 100); // 3
    ottox->_tone(note_A4, 400, 100); // 2
    ottox->_tone(note_A4, 400, 100); // 2
    ottox->_tone(note_G4, 800, 200); // 1
}

void PlayMusic::playGirlSong(Otto *ottox)
{
    // 第一段：1 2 231 2 5 | 23·2 1 6 | 1 2 231 2 5 | 56·3 2 1 | 1 2 231 2 5
    ottox->_tone(note_C4, 400, 100); // 1
    ottox->_tone(note_D4, 400, 100); // 2
    ottox->_tone(note_D4, 200, 50);
    ottox->_tone(note_E4, 200, 50);
    ottox->_tone(note_C4, 400, 100); // 231
    ottox->_tone(note_D4, 400, 100);
    ottox->_tone(note_G4, 400, 100); // 2 5
    ottox->_tone(note_D4, 150, 38);
    ottox->_tone(note_E4, 150, 38);
    ottox->_tone(note_D4, 400, 100); // 23·2
    ottox->_tone(note_C4, 400, 100);
    ottox->_tone(note_A4, 400, 100); // 1 6
    // 重复 1 2 231 2 5
    ottox->_tone(note_C4, 400, 100);
    ottox->_tone(note_D4, 400, 100);
    ottox->_tone(note_D4, 200, 50);
    ottox->_tone(note_E4, 200, 50);
    ottox->_tone(note_C4, 400, 100);
    ottox->_tone(note_D4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    // 56·3 2 1
    ottox->_tone(note_G4, 150, 38);
    ottox->_tone(note_A4, 150, 38);
    ottox->_tone(note_E4, 400, 100);
    ottox->_tone(note_D4, 400, 100);
    ottox->_tone(note_C4, 400, 100);
    // 重复 1 2 231 2 5
    ottox->_tone(note_C4, 400, 100);
    ottox->_tone(note_D4, 400, 100);
    ottox->_tone(note_D4, 200, 50);
    ottox->_tone(note_E4, 200, 50);
    ottox->_tone(note_C4, 400, 100);
    ottox->_tone(note_D4, 400, 100);
    ottox->_tone(note_G4, 400, 100);

    // 第二段：23·2 1 6 | 1 2 231 2 5 | 1 2 3 1 | 0 3 3 3 2 1 2 1
    ottox->_tone(note_D4, 150, 38);
    ottox->_tone(note_E4, 150, 38);
    ottox->_tone(note_D4, 400, 100);
    ottox->_tone(note_C4, 400, 100);
    ottox->_tone(note_A4, 400, 100);
    // 重复 1 2 231 2 5
    ottox->_tone(note_C4, 400, 100);
    ottox->_tone(note_D4, 400, 100);
    ottox->_tone(note_D4, 200, 50);
    ottox->_tone(note_E4, 200, 50);
    ottox->_tone(note_C4, 400, 100);
    ottox->_tone(note_D4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    // 1 2 3 1
    ottox->_tone(note_C4, 400, 100);
    ottox->_tone(note_D4, 400, 100);
    ottox->_tone(note_E4, 400, 100);
    ottox->_tone(note_C4, 400, 100);
    // 0 3 3 3 2 1 2 1
    ottox->_tone(0, 400, 100);
    ottox->_tone(note_E4, 400, 100);
    ottox->_tone(note_E4, 400, 100);
    ottox->_tone(note_E4, 400, 100);
    ottox->_tone(note_D4, 400, 100);
    ottox->_tone(note_C4, 400, 100);
    ottox->_tone(note_D4, 400, 100);
    ottox->_tone(note_C4, 400, 100);

    // 第三段：0 3 5 6 6 5 3 6 5 3 | 3 0 6 6 5 2 1 2 | 1 6· 0 0 0
    ottox->_tone(0, 400, 100);
    ottox->_tone(note_E4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    ottox->_tone(note_A4, 400, 100);
    ottox->_tone(note_A4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    ottox->_tone(note_E4, 400, 100);
    ottox->_tone(note_A4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    ottox->_tone(note_E4, 400, 100);
    // 3 0 6 6 5 2 1 2
    ottox->_tone(note_E4, 400, 100);
    ottox->_tone(0, 400, 100);
    ottox->_tone(note_A4, 400, 100);
    ottox->_tone(note_A4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    ottox->_tone(note_D4, 400, 100);
    ottox->_tone(note_C4, 400, 100);
    ottox->_tone(note_D4, 400, 100);
    // 1 6· 0 0 0
    ottox->_tone(note_C4, 400, 100);
    ottox->_tone(note_A4, 300, 75); // 附点八分
    ottox->_tone(0, 400, 100);
    ottox->_tone(0, 400, 100);
    ottox->_tone(0, 400, 100);

    // 第四段：0·5 5 5 5 6 5 3 5 | 6 5 3 5 6 6 5 1 | 6 5 5 3 3 5 6 5 1 2 3 3 | 21·1 0 0 0
    ottox->_tone(0, 300, 75);
    ottox->_tone(note_G4, 400, 100); // 0·5
    ottox->_tone(note_G4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    ottox->_tone(note_A4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    ottox->_tone(note_E4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    // 6 5 3 5 6 6 5 1
    ottox->_tone(note_A4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    ottox->_tone(note_E4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    ottox->_tone(note_A4, 400, 100);
    ottox->_tone(note_A4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    ottox->_tone(note_C4, 400, 100);
    // 6 5 5 3 3 5 6 5 1 2 3 3
    ottox->_tone(note_A4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    ottox->_tone(note_E4, 400, 100);
    ottox->_tone(note_E4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    ottox->_tone(note_A4, 400, 100);
    ottox->_tone(note_G4, 400, 100);
    ottox->_tone(note_C4, 400, 100);
    ottox->_tone(note_D4, 400, 100);
    ottox->_tone(note_E4, 400, 100);
    ottox->_tone(note_E4, 400, 100);
    // 21·1 0 0 0
    ottox->_tone(note_D4, 150, 38);
    ottox->_tone(note_C4, 150, 38); // 21·
    ottox->_tone(note_C4, 400, 100);
    ottox->_tone(0, 400, 100);
    ottox->_tone(0, 400, 100);
    ottox->_tone(0, 400, 100);
}

void PlayMusic::playRandomSong(Otto *ottox)
{
    // 随机播放一首歌曲
    int songIndex = random(0, 3); // 假设有三首歌
    switch (songIndex)
    {
    case 0:
        happyNewYear(ottox);
        break;
    case 1:
        twinkleStar(ottox);
        break;
    case 2:
        playGirlSong(ottox);
        break;
    default:
        break;
    }
}