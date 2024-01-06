#include <iostream>
#include<vector>
#include<map>
#include<string>
#include<set>
#include<exception>
#include<stdexcept>
#include<mutex>
using namespace std;

mutex myMutex;

// ============================ Enums ==================

enum ContestDifficultyLevel {Low, Medium, Hard};
enum QuestionDifficultyLevel {Low, Medium, Hard};
enum ContestState {Init, Running, End};

// ================= User ===============
class User{
    private:
    string name;
    map<Contest,int> contestToScoreMap;

    public:
    User() = delete; // This makes sure that default constructor can never be called
    User(string name):name(name){}

    void updateScoreForContest(int score, Contest contest)
    {
        contestToScoreMap[contest] = score;
    }
};

// ===================== Question ======================
class Question{
    private:
    int score;
    string questionBody;
    QuestionDifficultyLevel difficulty;

    public:
    Question() = delete;

    Question(int score,string questionBody, QuestionDifficultyLevel difficulty):score(score), questionBody(questionBody),difficulty(difficulty){}
    QuestionDifficultyLevel getDifficulty()
    {
        return difficulty;
    }
};

// =========================== UserContextForContest =========

class UserContextForContest{
    private:
    User user;
    Contest contest;
    vector<Question> questionsSolved;

    bool isValidQuestion(Question question){
        vector<Question> contestQuestions = contest.getQuestions();
        return find(contestQuestions.begin(),contestQuestions.end(),question) != contestQuestions.end();
    }
    public:
    UserContextForContest() = delete;
    UserContextForContest(User user, Contest contest):user(user),contest(contest){}
    void addASolvedQuestion(Question question) noexcept(false) {
        if(!isValidQuestion(question))
        {
            throw exception("Question is not a part of the contest");
        }
        questionsSolved.push_back(question);
    }
    int calculateScoreForUser(){
        int score;
        // Score calculation logic
        return score;
    }
};
// ========================== Contest ===================

class Contest{
    private:
    int contestId;
    vector<Question> questions;
    User creator;
    ContestState contestState;
    set<User> participants;
    map<User,UserContextForContest> userToUserContextMap;
    ContestDifficultyLevel difficulty;
    // startTime and endTime , not sure of their types in cpp

    bool isContestRunning()
    {
        return contestState == Running ;
    }
    bool isContestOver()
    {
        return contestState == End;
    }
    bool isQuestionValid(Question question)
    {
        return question.getDifficulty() == difficulty;
    }

    public:

    Contest() = delete;
    Contest(int contestId,User creator,vector<Question> questions, ContestDifficultyLevel difficulty):contestId(contestId),creator(creator),questions(questions),difficulty(difficulty){
        for(Question q:questions)
        {
            if(!isQuestionValid(q))
            {
                throw exception("The difficulty level of the question and contest do not match");
            }
        }
        contestState = Init;
    }
    void startContest(){
        contestState = Running;
    }
    void endContest(){
        contestState = End;
        for(User user:participants)
        {
            int score = calculateScoreForUser(user);
            updateScoreForUserInUserObject(score, user);
        }
    }
    void addQuestion(Question question){
        if(isContestRunning() || isContestOver())
        {
            throw exception("Can't add a question to Contest which is running or has ended");
        }
        if(!isQuestionValid(question))
        {
            throw exception("The difficulty level of the question and contest do not match");
        }
        questions.push_back(question);
    }
    vector<Question> getQuestions(){
        return questions;
    }
    UserContextForContest getUserContextForUser(User user)
    {
        if(userToUserContextMap.find(user) == userToUserContextMap.end())
        {
            throw exception("No user context for the user");
        }
        return userToUserContextMap[user];
    }
    void markQuestionSolvedForUser(User user, Question question)
    {
        UserContextForContest userContext = getUserContextForUser(user);
        userContext.addASolvedQuestion(question);
    }
    int calculateScoreForUser(User user)
    {   
        UserContextForContest userContext = getUserContextForUser(user);
        int score = userContext.calculateScoreForUser();
        return score;
    }
    void updateScoreForUserInUserObject(int score, User user)
    {
        UserService* userServicePtr = UserService::getInstance();
        userServicePtr->updateContestScoreForUser(user,*this,score);
    }
    void addParticipant(User user)
    {
        UserContextForContest userContext = UserContextForContest(user, *this);
        participants.insert(user);
        userToUserContextMap[user] = userContext;
    }
    void removeParticipant(User user)
    {
        if(participants.find(user)!=participants.end())
        {
            participants.erase(participants.find(user));
        }
        else
        {
            throw exception("User not a participant in the contest");
        }

        if(userToUserContextMap.find(user)!=userToUserContextMap.end())
        {
            UserContextForContest userContext = userToUserContextMap[user];
            userToUserContextMap.erase(userToUserContextMap.find(user));
            delete &userContext;
        }
        else
        {
            throw exception("No User context was created for the user and the current contest");
        }
    }
    vector<User> rankParticipants(){
        if(!isContestOver())
        {
            throw exception("Can't produce ranking for an unfinished contest");
        }
        // Logic to rank the participants
    }
};


// =================== ContestService (Thread Safe singleton desing pattern) ==============

/* Contest Service will handle everything that has anything to do with the contest*/

class ContestService{
    private:
    static ContestService* instance;
    map<int, Contest> contestIdToContestMap;

    ContestService(){}

    public:
    static ContestService* getInstance(){
        lock_guard<mutex> lock(myMutex);
        if(!instance){
            instance = new ContestService();
        }
        return instance;
    }
    Contest createContest(User creator,vector<Question> questions, ContestDifficultyLevel difficulty){
        int contestId;
        // some logic to create the contestId
        Contest contest = Contest(contestId, creator, questions, difficulty);
        contestIdToContestMap[contestId] = contest;
        return contest;
    }
    Contest getContest(int contestId){
        if(contestIdToContestMap.find(contestId)==contestIdToContestMap.end())
        {
            throw exception("Unknown contest id encountered");
        }
        return contestIdToContestMap[contestId];
    }
    void startContest(int contestId)
    {
        Contest contest = getContest(contestId);
        contest.startContest();
    }
    void endContest(int contestId) // This method may be called by an asynchronous job to end a timed contest
    {
        Contest contest = getContest(contestId);
        contest.endContest();
    }
    vector<Contest> listContestsByDifficulty(ContestDifficultyLevel difficulty){
        // Logic to list contests by difficulty
    }
    void addQuestionToContest(Question question, int contestId)
    {
        Contest contest = getContest(contestId);
        contest.addQuestion(question);
    }
    void addParticipantToContest(User user, int contestId)
    {
        Contest contest = getContest(contestId);
        contest.addParticipant(user);
    }
    void withdrawParticipationFromContest(User user,int contestId)
    {
        Contest contest = getContest(contestId);
        contest.removeParticipant(user);
    }

};

// ========================== UserService (Thread safe Singleton design pattern) =====================

/* UserService will handle anything that is related to users*/
class UserService{
    private:
    static UserService* instance;
    set<User> users;
    UserService(){}

    public:
    static UserService* getInstance(){
        lock_guard<mutex> lock(myMutex);
        if(instance == NULL){
            instance = new UserService();
        }
        return instance;
    }
    User createUser(string name){
        User user = User(name);
        users.insert(user);
        return user;
    } 
    void updateContestScoreForUser(User user,Contest contest, int score)
    {
        user.updateScoreForContest(score, contest);
    }
    vector<User> rankUsers()
    {
        // logic to rank all the users
    }
};

// =================== QuestionService (Thread safe Singleton design pattern) =================

/* QuestionService will handle anything that is related to questions*/
class QuestionService{
    private:
    static QuestionService* instance;
    set<Question> questions;
    QuestionService(){}

    public:
    static QuestionService* getInstance(){
        lock_guard<mutex> lock(myMutex);
        if(instance == NULL){
            instance = new QuestionService();
        }
        return instance;
    }
    Question createQuestion(string questionBody,QuestionDifficultyLevel difficulty, int score){
        Question question = Question(score, questionBody, difficulty);
        questions.insert(question);
        return question;
    } 

    vector<Question> listQuestionsByDIfficulty(QuestionDifficultyLevel difficulty)
    {
        // logic to list questions by difficulty
    }
};