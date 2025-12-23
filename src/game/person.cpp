#include "gameengine.h"
#include "company.h"

NameGenerator::NameGenerator()
{
}

void loadNamensIntoVector(std::vector<ppl7::String>& target, const ppl7::String& locale, const ppl7::String& filename)
{
    ppl7::File ff;
    try {
        ff.open("res/locales/" + locale + "/" + filename, ppl7::File::READ);
        while (!ff.eof()) {
            ppl7::String line = ff.gets();
            line.trim();
            if (line.isEmpty()) continue;
            target.push_back(line);
        }
        ff.close();

    }
    catch (const ppl7::EndOfFileException& exp) {}
    catch (const ppl7::Exception& exp) {
        exp.print();
    }
}

void NameGenerator::loadNames(const ppl7::String& locale)
{
    loadNamensIntoVector(second_names, locale, "secondnames.txt");
    loadNamensIntoVector(male, locale, "firstnames_male.txt");
    loadNamensIntoVector(female, locale, "firstnames_female.txt");
    ppl7::PrintDebug("Loaded %d male, %d female and %d second names\n", male.size(), female.size(), second_names.size());
}

ppl7::String NameGenerator::randomName(Gender::GenderType gender)
{
    size_t sn = ppl7::rand(0, second_names.size() - 1);
    if (gender == Gender::Male) {
        size_t fn = ppl7::rand(0, male.size() - 1);
        return ppl7::String(male[fn] + " " + second_names[sn]);
    }
    else {
        size_t fn = ppl7::rand(0, female.size() - 1);
        return ppl7::String(female[fn] + " " + second_names[sn]);
    }
}


Person::Person(const ppl7::String& name)
    : name(name)
{
}

