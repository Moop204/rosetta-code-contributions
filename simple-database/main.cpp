#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <map>
#include <memory>

class Entry
{
public:
  Entry(std::string t, std::string d, std::vector<std::string> tags)
  {
    //std::time_t timer = std::time(nullptr);
    //this->time = (std::localtime(&timer));
    this->title = t;
    this->description = d;
    this->tags = tags;
  }
  ~Entry()
  {
    this->title.clear();
    this->description.clear();
    this->tags.clear();
  }
  std::string getTitle()
  {
    return this->title;
  }
  std::string getDescription()
  {
    return this->description;
  }
  std::vector<std::string> getTags()
  {
    return this->tags;
  }
  bool hasTag(std::string search)
  {
    for (auto elm : tags)
    {
      if (elm == search)
      {
        return true;
      }
    }
    return false;
  }

private:
  std::string title;
  std::string description;
  std::vector<std::string> tags;
  // Replace with smart pointer?
  //struct tm time;
};

typedef std::map<std::string, std::unique_ptr<Entry>> TagEntry;

class Database
{
private:
  std::unique_ptr<std::vector<Entry>> entries;
  std::unique_ptr<Entry> lastEntry;
  std::map<std::string, std::unique_ptr<Entry>> lastOfCategories;
  //std::map<std::string, Entry> lastOfCategories;
  void printEntry(Entry e)
  {
    std::string tagString = "";
    for (auto elm : e.getTags())
    {
      tagString += ("][" + elm);
    }
    std::cout << "[DATE] " + e.getTitle() + " " + tagString << std::endl
              << e.getDescription() << std::endl;
  }

public:
  Database()
  {
    this->entries = std::make_unique<std::vector<Entry>>();
    this->lastEntry = NULL;              //std::make_unique<Entry>();
    this->lastOfCategories = TagEntry(); //NULL;
  }

  ~Database()
  {
    auto stuff = entries.get();
    stuff->clear();

    /*
    auto del1 = this->lastEntry.release();
    delete del1;
    //auto tmp = this->entries.release();
    auto tmp = this->entries.get();
    tmp->clear();
    delete tmp;
    */
    //auto del2 = this->entries.release();
    //delete del2;
  }

  void addEntry(std::string t, std::string d, std::vector<std::string> &tags)
  {
    //auto nEntry = new Entry(t, d, tags);
    auto stuff = entries.get();
    stuff->push_back(Entry(t, d, tags));
    this->lastEntry.release();
    this->lastEntry = std::make_unique<Entry>(stuff->back());

    for (std::string tag : tags)
    {
      if (this->lastOfCategories.find(tag) != this->lastOfCategories.end())
      {
        //this->lastOfCategories.erase(tag);
      }
      auto tmp = std::make_unique<Entry>(stuff->back());
      this->lastOfCategories.insert({tag, std::move(tmp)});
    }
    return;
  }

  void printLastEntry()
  {
    if (this->lastEntry == NULL)
    {
      std::cout << "No entry available.\n";
      return;
    }
    std::cout << "Last added entry:" << std::endl;
    this->printEntry(*(this->lastEntry));
  }

  void printLastEntryCategory()
  {
    std::cout << "Last entry by Category:" << std::endl;

    //std::map<std::string, std::unique_ptr<Entry>> categories = this->lastOfCategories;
    for (auto iter = this->lastOfCategories.begin(); iter != this->lastOfCategories.end(); ++iter)
    {
      //auto elm = *iter;
      std::cout << iter->first << std::endl;
      this->printEntry(*(iter->second).get());
    }
  }

  void printEntries()
  {
    auto eVec = *this->entries.get();
    if (eVec.size() == 0)
    {
      std::cout << "There are no entries" << std::endl;
      return;
    }
    std::cout << "Current Entries:" << std::endl;
    for (auto entry : eVec)
    {
      printEntry(entry);
    }
  }
};

void test(std::vector<Entry> &v)
{
  std::vector<std::string> test_tags = {"Dogs", "Cats", "Bee"};
  auto e = Entry("Test", "Desc", test_tags);
  v.push_back(e);
  v.push_back(e);
  v.push_back(e);
}

int main(void)
{
  std::vector<Entry> ve;
  test(ve);
  //delete e;
  auto db = new Database();
  std::vector<std::string> tags = {"Dogs", "Cats", "Bee"};
  db->addEntry("BEEP", "YEET a test string", tags);
  db->printLastEntry();
  db->printLastEntryCategory();
  db->addEntry("Tessdfsdfsfsfsfafast", "This is a testdsfafasfsafasfasfasfdsvxv c xrytitjnbxdfsrtjyk string", tags);
  db->printLastEntry();
  db->printLastEntryCategory();
  db->printEntries();
  delete db;
}
