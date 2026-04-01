#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

// ---------------------- NewsArticle ----------------------
class NewsArticle {
private:
    string title, content, source;

public:
    void input() {
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Content: ";
        getline(cin, content);
        cout << "Enter Source: ";
        getline(cin, source);
    }

    string getTitle() const { return title; }
    string getContent() const { return content; }
    string getSource() const { return source; }

    // Save to file
    void saveToFile(string filename, int score, string result) {
        ofstream out(filename, ios::app);
        if (!out) {
            cout << "Error saving file!\n";
            return;
        }

        out << title << "|" << content << "|" << source
            << "|" << score << "|" << result << endl;

        out.close();
    }
};

// ---------------------- Abstract Rule ----------------------
class Rule {
public:
    virtual int evaluate(const NewsArticle& article) = 0;
    virtual string getName() = 0;
    virtual string explain() = 0;
};

// ---------------------- Keyword Rule ----------------------
class KeywordRule : public Rule {
    int score;
    string explanation;

public:
    int evaluate(const NewsArticle& article) override {
        vector<string> keywords = {"shocking", "breaking", "secret"};
        string content = article.getContent();

        score = 0;
        explanation = "No issue";

        for (string word : keywords) {
            if (content.find(word) != string::npos) {
                score = -20;
                explanation = "Sensational keyword: " + word;
                break;
            }
        }
        return score;
    }

    string getName() override { return "Keyword Rule"; }
    string explain() override { return explanation; }
};

// ---------------------- Source Rule ----------------------
class SourceRule : public Rule {
    int score;
    string explanation;

public:
    int evaluate(const NewsArticle& article) override {
        vector<string> trusted = {"bbc.com", "reuters.com", "thehindu.com"};
        string src = article.getSource();

        if (find(trusted.begin(), trusted.end(), src) != trusted.end()) {
            score = 30;
            explanation = "Trusted source";
        } else {
            score = -30;
            explanation = "Untrusted source";
        }
        return score;
    }

    string getName() override { return "Source Rule"; }
    string explain() override { return explanation; }
};

// ---------------------- Title Match Rule ----------------------
class TitleRule : public Rule {
    int score;
    string explanation;

public:
    int evaluate(const NewsArticle& article) override {
        string title = article.getTitle();
        string content = article.getContent();

        if (content.find(title.substr(0, 5)) != string::npos) {
            score = 10;
            explanation = "Title matches content";
        } else {
            score = -20;
            explanation = "Title mismatch";
        }
        return score;
    }

    string getName() override { return "Title Rule"; }
    string explain() override { return explanation; }
};

// ---------------------- Score Engine ----------------------
class ScoreEngine {
    vector<Rule*> rules;

public:
    void addRule(Rule* r) {
        rules.push_back(r);
    }

    int calculateScore(const NewsArticle& article) {
        int total = 50;

        cout << "\n--- Rule Evaluation ---\n";
        for (Rule* r : rules) {
            int impact = r->evaluate(article);
            cout << r->getName() << ": " << impact
                 << " | " << r->explain() << endl;
            total += impact;
        }
        return total;
    }
};

// ---------------------- Display File ----------------------
void displayAll(string filename) {
    ifstream in(filename);
    if (!in) {
        cout << "No data found.\n";
        return;
    }

    string line;
    cout << "\n------ Saved Articles ------\n";

    while (getline(in, line)) {
        int p1 = line.find("|");
        int p2 = line.find("|", p1 + 1);
        int p3 = line.find("|", p2 + 1);
        int p4 = line.find("|", p3 + 1);

        cout << "\nTitle: " << line.substr(0, p1);
        cout << "\nSource: " << line.substr(p2 + 1, p3 - p2 - 1);
        cout << "\nScore: " << line.substr(p3 + 1, p4 - p3 - 1);
        cout << "\nResult: " << line.substr(p4 + 1);
        cout << "\n----------------------------\n";
    }

    in.close();
}

// ---------------------- Search ----------------------
void searchArticle(string filename) {
    ifstream in(filename);
    string keyword, line;
    bool found = false;

    cout << "Enter keyword: ";
    getline(cin, keyword);

    while (getline(in, line)) {
        if (line.find(keyword) != string::npos) {
            cout << "\nFound: " << line << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No match found.\n";

    in.close();
}

// ---------------------- Detector ----------------------
string classify(int score) {
    if (score >= 80) return "RELIABLE";
    else if (score >= 50) return "SUSPICIOUS";
    else return "FAKE";
}

// ---------------------- Main ----------------------
int main() {
    ScoreEngine engine;
    engine.addRule(new KeywordRule());
    engine.addRule(new SourceRule());
    engine.addRule(new TitleRule());

    int choice;

    do {
        cout << "\n===== Fake News Detector =====\n";
        cout << "1. Analyze News\n";
        cout << "2. View Saved\n";
        cout << "3. Search\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            NewsArticle article;
            article.input();

            int score = engine.calculateScore(article);
            string result = classify(score);

            cout << "\nFinal Score: " << score;
            cout << "\nResult: " << result << endl;

            article.saveToFile("news.txt", score, result);

        } else if (choice == 2) {
            displayAll("news.txt");

        } else if (choice == 3) {
            searchArticle("news.txt");
        }

    } while (choice != 4);

    return 0;
}