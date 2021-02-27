#include <iostream>
#include <vector>
#include <cstring>

class AsciiLine{

private:
    char* m_Line;
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
        memcpy(m_Line, asciiLine.m_Line, asciiLine.m_Size);
    }

    ~AsciiLine() {
        delete[] m_Line;
    }

//Methods
public:

    void replace(int index, const char* string) {

            //Replace the char's with the char's in string, -1 because the '\n' is not needed here
            for (int i  = 0; i < strlen(string) - 1; i++)
            {
                m_Line[index + i] = string[i];
            }

    }

    const char* toString() const {
        return m_Line;
    }

};

class AsciiBlock{

private:

    const int m_Height;
    const int m_Width;

protected:
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

    const AsciiLine& getAsciiLine(int index) const {
        return m_Block.at(index);
    }

    int getHeight() const {
        return m_Height;
    }

    friend std::ostream& operator<<(std::ostream &os, const AsciiBlock &block) {

        std::string entireBlock;
        for (const AsciiLine& line : block.m_Block) { entireBlock += line.toString(); }

        os << entireBlock;
        return os;
    }


};


class AsciiGrid: public AsciiBlock {

private:

    struct PlottedBlock {

        const AsciiBlock* asciiBlock;
        const int x, y;

        PlottedBlock(const AsciiBlock* asciiBlock, int x, int y) : asciiBlock(asciiBlock), x(x), y(y)
        {
        }

    };

    std::vector<PlottedBlock> m_PlottedAscii;

public:

    static const int width{50};

    static const int height{50};

public:

    AsciiGrid() : AsciiBlock(height, width, '`')
    {
    }

    //Copy AsciiBlock to allow for the same block to be graphed
    void plot(AsciiBlock asciiBlock, int x, int y)
    {
        //Add to list of objects graphed
        m_PlottedAscii.emplace_back(&asciiBlock, x, y);

        //Replace existing AsciiLine's with asciiBlock's AsciiLines
        for (int i = y; i < asciiBlock.getHeight() + y; i++)
        {
            m_Block.at(i).replace(x,asciiBlock.getAsciiLine(i - y).toString());
        }

    }

};

int main()
{

    AsciiBlock f(10, 5, '#');
    AsciiGrid a;
    a.plot(f, 20, 10);
//    std::cout << a;
    a.plot(f, 0, 0);
    std::cout << a;

    return 0;
}
