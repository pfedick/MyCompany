#include "gameengine.h"
#include "company.h"

NameGenerator::NameGenerator()
{
}

void NameGenerator::loadNames(const ppl7::String& locale)
{
    ppl7::File ff;
    ff.open("res/locales/" + locale + "/secondnames.txt", ppl7::File::READ);
    while (!ff.eof()) {
        ppl7::String line = ff.gets();
        line.trim();
        if (line.isEmpty()) continue;
        second_names.push_back(line);
    }
    ff.close();
    ff.open("res/locales/" + locale + "/firstnames_male.txt", ppl7::File::READ);
    while (!ff.eof()) {
        ppl7::String line = ff.gets();
        line.trim();
        if (line.isEmpty()) continue;
        male.push_back(line);
    }
    ff.close();
    ff.open("res/locales/" + locale + "/firstnames_female.txt", ppl7::File::READ);
    while (!ff.eof()) {
        ppl7::String line = ff.gets();
        line.trim();
        if (line.isEmpty()) continue;
        female.push_back(line);
    }
    ff.close();
    ppl7::PrintDebug("Loaded %d male, %d female and %d second names\n", male.size(), female.size(), second_names.size());

}

Person::Person(const ppl7::String& name)
    : name(name)
{
}

