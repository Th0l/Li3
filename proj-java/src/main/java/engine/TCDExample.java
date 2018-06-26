package engine;

import common.MyLog;
import common.Pair;
import common.Community;
import engine.Clean;
import engine.Query1;
import engine.Query2;
import engine.Query3;
import engine.Query4;
import engine.Query5;
import engine.Query6;
import engine.Query7;
import engine.Query8;
import engine.Query9;
import engine.Query10;
import engine.Query11;
import li3.TADCommunity;

import java.time.LocalDate;
import java.util.Arrays;
import java.util.List;

public class TCDExample implements TADCommunity {

    private MyLog qelog;

    /*
    public void init() {
        this.qelog = new MyLog("queryengine");
    }
    */

    Community com = new Community();
    Clean cl = new Clean();
    Query1 q1 = new Query1();
    Query2 q2 = new Query2();
    Query3 q3 = new Query3();
    Query4 q4 = new Query4();
    Query5 q5 = new Query5();
    Query6 q6 = new Query6();
    Query7 q7 = new Query7();
    Query8 q8 = new Query8();
    Query9 q9 = new Query9();
    Query10 q10 = new Query10();
    Query11 q11 = new Query11();

    public void load(String dumpPath) {
          com.load(dumpPath);
    }

    // Query 1
    public Pair<String,String> infoFromPost(long id) {
        return q1.query1(id);
    }

    // Query 2
    public List<Long> topMostActive(int N) {
        return q2.query2(N);
    }

    // Query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
        long bg = (long)((begin.getYear() * 10000)+(begin.getMonthValue() * 100)+(begin.getDayOfMonth()));
        long ed = (long)((end.getYear() * 10000)+(end.getMonthValue() * 100)+(end.getDayOfMonth()));
        return q3.query3(bg,ed);
    }

    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
        long bg = (long)((begin.getYear() * 10000)+(begin.getMonthValue() * 100)+(begin.getDayOfMonth()));
        long ed = (long)((end.getYear() * 10000)+(end.getMonthValue() * 100)+(end.getDayOfMonth()));
        return q4.query4(tag,bg,ed);
    }

    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id) {
        return q5.query5(id);
    }

    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
        long bg = (long)((begin.getYear() * 10000)+(begin.getMonthValue() * 100)+(begin.getDayOfMonth()));
        long ed = (long)((end.getYear() * 10000)+(end.getMonthValue() * 100)+(end.getDayOfMonth()));
        return q6.query6(N,bg,ed);
    }

    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        long bg = (long)((begin.getYear() * 10000)+(begin.getMonthValue() * 100)+(begin.getDayOfMonth()));
        long ed = (long)((end.getYear() * 10000)+(end.getMonthValue() * 100)+(end.getDayOfMonth()));
        return q7.query7(N,bg,ed);
    }

    // Query 8
    public List<Long> containsWord(int N, String word) {
        return q8.query8(word,N);
    }

    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2) {
        return q9.query9(id1,id2,N);
    }

    // Query 10
    public long betterAnswer(long id) {
        return q10.query10(id);
    }

    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
        long bg = (long)((begin.getYear() * 10000)+(begin.getMonthValue() * 100)+(begin.getDayOfMonth()));
        long ed = (long)((end.getYear() * 10000)+(end.getMonthValue() * 100)+(end.getDayOfMonth()));
        return q11.query11(N,bg,ed);
    }

    public void clear(){
        cl.clear();
    }
}
