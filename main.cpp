#include <iostream>
#include <vector>
#include <cstring>

class AsciiLine{

private:
    char *m_Line;
    int m_Size;

//Constructors
public:

    AsciiLine(const char asciiCharacter, int width)
    {
        m_Size = width + 1;
        m_Line = new char[m_Size];

        for (int i = 0; i < m_Size - 1; i++) { m_Line[i] = asciiCharacter; }

        //All asciiLines end in a new m_Line
        m_Line[m_Size - 1] = '\n';

        //Add termination char
        m_Line[m_Size] = 0;
    }

    explicit AsciiLine(const char* string)
    {
        int size = strlen(string);
        m_Size = size + 2;

        m_Line = new char[m_Size];
        memcpy(m_Line, string, size);

        //All asciiLines end in a new m_Line
        m_Line[size] = '\n';
    };

    AsciiLine(const AsciiLine& asciiLine) : m_Size(asciiLine.m_Size)
    {
        m_Line = new char[m_Size];
        memcpy(m_Line, asciiLine.m_Line, m_Size);
    }

    ~AsciiLine() {
        delete[] m_Line;
    }

//Methods
public:

    void replace(int index, const char* string)
    {
            //Replace the char's with the char's in string, -1 because the '\n' is not needed here
            for (int i  = 0; i < strlen(string) - 1; i++)
            {
                m_Line[index + i] = string[i];
            }

    }

    const char* toString()
    {
        return m_Line;
    }

};

class AsciiBlock{

private:

    const int m_Height;
    const int m_Width;
    std::vector<AsciiLine> m_Block;

public:

    AsciiBlock(const int height, const int width, const char asciiCharacter) : m_Height(height), m_Width(width)
    {

        m_Block.reserve(height);
        for (int i = 0; i < m_Height; i++)
        {
            m_Block.emplace_back(asciiCharacter, m_Width);
        }

    }

    AsciiLine& getAsciiLine(int index)
    {
        return m_Block.at(index);
    }

    int getHeight() const {
        return m_Height;
    }

    int getWidth() const {
        return m_Width;
    }

    void print() {

        //Print the entire frame (grid) at a time by constructing it into one string.
        std::string entireBlock;
        for (AsciiLine& line : m_Block) { entireBlock += line.toString(); }

        std::cout << entireBlock;
    }


};


class AsciiGrid: public AsciiBlock {

private:

    std::vector<AsciiBlock*> m_PlottedAscii;

public:

    static const int width{15};

    static const int height{15};

public:

    AsciiGrid() : AsciiBlock(height, width, ' ')
    {
    }

    void plot(AsciiBlock *asciiBlock, int const xOrigin, int const yOrigin)
    {
        //Add to list of objects graphed
        m_PlottedAscii.push_back((AsciiBlock *const) asciiBlock);

        for (int i = yOrigin; i < asciiBlock->getHeight() + yOrigin; i++)
        {
            this->getAsciiLine(i).replace(
                    xOrigin,
                    asciiBlock->getAsciiLine(0).toString()
                    );
        }


    }

};

int main()
{

    AsciiBlock* l = new AsciiBlock(3, 3, 'e');
    AsciiGrid a;
    a.plot(l, 10, 10);
    a.print();

    return 0;
}
