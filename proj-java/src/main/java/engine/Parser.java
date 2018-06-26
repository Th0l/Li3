
/**
 * Classe que vai dar parse aos diferentes ficheiros xml
 *
 * @author (your name)
 * @version (a version number or a date)
 */
package engine;

import common.help_struct_1;
import common.help_struct_2;
import common.posts_str;
import common.postXusr;
import common.users_str;
import common.usrXpost;

import java.io.File;
import java.io.IOException;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import java.util.Set;
import java.util.Map;
import java.util.HashMap;
import java.util.Iterator;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

public class Parser
{
   public final static HashMap<Long,users_str> infoU = new HashMap();
   public final static HashMap<Long,posts_str> infoP = new HashMap();
    /**
     *
     */
    public HashMap<Long,users_str> userParser(String path)
    {
      try {
         File inputFile = new File(path);
         SAXParserFactory factory = SAXParserFactory.newInstance();
         SAXParser saxParser = factory.newSAXParser();
         UserHandler userhandler = new UserHandler();
         saxParser.parse(inputFile, userhandler);
      } catch (Exception e) {
         e.printStackTrace();
      }
      System.out.println("Parse Users Over");
      return infoU;
   }

   class UserHandler extends DefaultHandler {


      @Override
      public void startElement(
         String uri, String localName, String qName, Attributes attributes)
         throws SAXException {

         if (qName.equalsIgnoreCase("row")) {
            String Id; //= attributes.getValue("Id");
            String Rep; //= attributes.getValue("Reputation");
            String Nome; //= attributes.getValue("DisplayName");
            String Bio; //= attributes.getValue("AboutMe");
            long rept,idu;
            if(attributes.getValue("Id") != null){
                Id = attributes.getValue("Id");
                idu = Long.parseLong(Id);
            }
            else
                idu = -2;
            if(attributes.getValue("Reputation") != null){
                Rep = attributes.getValue("Reputation");
                rept = Long.parseLong(Rep);
            }
            else
                rept = -2;
            if(attributes.getValue("AboutMe") != null)
                Bio = attributes.getValue("AboutMe");
            else
                Bio = "Nothing";
            if(attributes.getValue("DisplayName") != null)
                Nome = attributes.getValue("DisplayName");
            else
                Nome = "Nothing";

            users_str insert = new users_str(idu,rept,Bio,Nome);

            infoU.put(idu,insert);
         }
      }
   }

    /**
     * Funçao getTime que vai ser usada para concatenar a data de publicaçao lida do ficheiro XML
     * String timeStr , ex : "2010-09-13T19:19:35.360"
     * returns long , ex : 20100913
     */
    private long getTime(String timeStr)
    {
        String ano = timeStr.substring(0,4);
        String mes = timeStr.substring(5,7);
        String dia = timeStr.substring(8,10);

        long year = Long.parseLong(ano);
        long month = Long.parseLong(mes);
        long day = Long.parseLong(dia);

        long date = (10000 * year) + (100 * month) + day;

        return date;
    }

    /**
     *
     *
     */
   public HashMap<Long,posts_str> postParser(String path)
   {
      try {
         File inputFile = new File(path);
         SAXParserFactory factory = SAXParserFactory.newInstance();
         SAXParser saxParser = factory.newSAXParser();
         PostHandler posthandler = new PostHandler();
         saxParser.parse(inputFile, posthandler);
      } catch (Exception e) {
         e.printStackTrace();
      }
      System.out.println("Parse Posts Over");
      return infoP;
   }
   class PostHandler extends DefaultHandler {


      @Override
      public void startElement(
         String uri, String localName, String qName, Attributes attributes)
         throws SAXException {

         if (qName.equalsIgnoreCase("row")) {
            String SpId,SpUId,SpType,SparId,Sscore,Scomm,titulo,tags,SdataNumber;
            long pId,pUId,pType,parId,score,comm,dataNumber;

            if(attributes.getValue("Id") != null){
                SpId = attributes.getValue("Id");
                pId = Long.parseLong(SpId);
            }
            else
                pId = -2;
            if(attributes.getValue("PostTypeId") != null){
                SpType = attributes.getValue("PostTypeId");
                pType = Long.parseLong(SpType);
            }
            else
                pType = -2;
            if(attributes.getValue("OwnerUserId") != null){
                SpUId = attributes.getValue("OwnerUserId");
                pUId = Long.parseLong(SpUId);
            }
            else
                pUId = -2;
            if(attributes.getValue("CommentCount") != null){
                Scomm = attributes.getValue("CommentCount");
                comm = Long.parseLong(Scomm);
            }
            else
                comm = -2;
            if(attributes.getValue("Score") != null){
                Sscore = attributes.getValue("Score");
                score = Long.parseLong(Sscore);
            }
            else
                score = -2;
            if(attributes.getValue("CreationDate") != null){
                SdataNumber = attributes.getValue("CreationDate");
                dataNumber = getTime(SdataNumber);
            }
            else
                dataNumber = -2;
            if(pType == 1){
                parId = -2;
                if(attributes.getValue("Title") != null)
                    titulo = attributes.getValue("Title");
                else
                    titulo = "Nothing";
                if(attributes.getValue("Tags") != null)
                    tags = attributes.getValue("Tags");
                else
                    tags = "Nothing";

                    posts_str insert =  new posts_str(pId,pUId,pType,parId,score,comm,dataNumber,titulo,tags);
                infoP.put(pId,insert);
            }
            if(pType == 2){
                titulo = "Nothing";
                tags = "Nothing";
                if(attributes.getValue("ParentId") != null){
                    SparId = attributes.getValue("ParentId");
                    parId = Long.parseLong(SparId);
                }
                else
                    parId = -2;

                posts_str insert =  new posts_str(pId,pUId,pType,parId,score,comm,dataNumber,titulo,tags);
                infoP.put(pId,insert);
            }
         }
      }
   }

    /**
     *
     *
     */
    public HashMap<String,Long> tagParser(String path)
    {
      HashMap<String,Long> info = new HashMap();

      try
      {
          File inputFile = new File(path);
          DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
          DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
          Document doc = dBuilder.parse(inputFile);
          doc.getDocumentElement().normalize();
          NodeList nList = doc.getElementsByTagName("row");

          for (int temp = 0; temp < nList.getLength(); temp++)
          {
              Node nNode = nList.item(temp);

              if (nNode.getNodeType() == Node.ELEMENT_NODE)
              {
                  Element eElement = (Element) nNode;
                  String tName = eElement.getAttribute("TagName");

                  if(!(tName.length() == 0))
                  {
                      String ctName = "<".concat(tName).concat(">");
                      long id = Long.parseLong(eElement.getAttribute("Id"));

                      info.put(ctName,id);
                  }
              }
          }
      }catch(Exception e){
            e.printStackTrace();
      }

      System.out.println("Parse Tags Over");

      return info;
    }

    /**
     *
     *
     */
    public HashMap<Long,usrXpost> xtraUserParse(HashMap<Long,posts_str> posts)
    {
        HashMap<Long,usrXpost> info = new HashMap();

        Iterator it = posts.entrySet().iterator();

        while(it.hasNext())
        {
            Map.Entry pair = (Map.Entry)it.next();
            posts_str post = (posts_str) pair.getValue();
            long usrID = post.getUsrID();
            long type;

            if(info.containsKey(usrID))
            {
                usrXpost sub = info.get(usrID);

                type = post.getType();

                if(type == 1)
                {
                    ArrayList<help_struct_1> postID = sub.getPostID();
                    ArrayList<help_struct_1> questionID = sub.getQuestID();
                    ArrayList<String> tags = sub.getTags();
                    long totalP = sub.getPostTot();

                    help_struct_1 insert = new help_struct_1(post.getID(),post.getData());
                    postID.add(insert);
                    help_struct_1 insert2 = new help_struct_1(post.getID(),post.getData());
                    questionID.add(insert2);
                    tags.add(post.getTags());
                    totalP ++;

                    Collections.sort(postID);
                    Collections.sort(questionID);

                    sub.setPostTot(totalP);
                    sub.setPostID(postID);
                    sub.setQuestID(questionID);
                    sub.setTags(tags);
                }
                else
                {
                    ArrayList<help_struct_1> postID = sub.getPostID();
                    ArrayList<help_struct_1> questionID = sub.getQuestID();
                    if(posts.containsKey(post.getParent()))
                    {
                        posts_str parent = posts.get(post.getParent());
                        long totalP = sub.getPostTot();

                        help_struct_1 insert = new help_struct_1(post.getID(),post.getData());
                        postID.add(insert);
                        help_struct_1 insert2 = new help_struct_1(post.getParent(),parent.getData());
                        questionID.add(insert2);
                        totalP++;

                        Collections.sort(postID);
                        Collections.sort(questionID);

                        sub.setPostTot(totalP);
                        sub.setPostID(postID);
                        sub.setQuestID(questionID);
                    }
                }
                info.replace(usrID,sub);
            }
            else
            {
                usrXpost sub = new usrXpost();

                type = post.getType();

                if(type == 1)
                {
                    ArrayList<help_struct_1> postID = sub.getPostID();
                    ArrayList<help_struct_1> questionID = sub.getQuestID();
                    ArrayList<String> tags = sub.getTags();
                    long totalP = sub.getPostTot();

                    help_struct_1 insert = new help_struct_1(post.getID(),post.getData());
                    postID.add(insert);
                    help_struct_1 insert2 = new help_struct_1(post.getID(),post.getData());
                    questionID.add(insert2);
                    tags.add(post.getTags());
                    totalP++;

                    Collections.sort(postID);
                    Collections.sort(questionID);

                    sub.setPostTot(totalP);
                    sub.setPostID(postID);
                    sub.setQuestID(questionID);
                    sub.setTags(tags);
                }
                else
                {
                    ArrayList<help_struct_1> postID = sub.getPostID();
                    ArrayList<help_struct_1> questionID = sub.getQuestID();
                    if(posts.containsKey(post.getParent()))
                    {
                        posts_str parent = posts.get(post.getParent());
                        long totalP = sub.getPostTot();

                        help_struct_1 insert = new help_struct_1(post.getID(),post.getData());
                        postID.add(insert);
                        help_struct_1 insert2 = new help_struct_1(post.getParent(),parent.getData());
                        questionID.add(insert2);
                        totalP++;

                        Collections.sort(postID);
                        Collections.sort(questionID);

                        sub.setPostTot(totalP);
                        sub.setPostID(postID);
                        sub.setQuestID(questionID);
                    }
                }
                info.put(usrID,sub);
            }
        }

        System.out.println("Extra User Parse Over");

        return info;
    }

    /**
     *
     *
     */
    public HashMap<Long,postXusr> xtraPostParse(HashMap<Long,posts_str> posts)
    {
        HashMap<Long,postXusr> info = new HashMap();

        Iterator it = posts.entrySet().iterator();

        while(it.hasNext())
        {
            Map.Entry pair = (Map.Entry)it.next();
            posts_str post = (posts_str) pair.getValue();
            long type = post.getType();
            long postID;

            if(type == 2)
            {
                postID = post.getParent();

                if(info.containsKey(postID))
                {
                    postXusr sub = info.get(postID);
                    long x = sub.getNumR();
                    ArrayList<help_struct_2> resp = sub.getRespostas();

                    help_struct_2 insert = new help_struct_2(post.getID(),post.getUsrID(),post.getData());
                    resp.add(insert);
                    x++;

                    Collections.sort(resp);

                    sub.setNumR(x);
                    sub.setRespostas(resp);

                    info.replace(postID,sub);
                }
                else
                {
                    if(posts.containsKey(postID))
                    {
                        postXusr sub = new postXusr();
                        posts_str parent = posts.get(postID);
                        ArrayList<help_struct_2> resp = sub.getRespostas();
                        long x = 1;

                        help_struct_2 insert = new help_struct_2(post.getID(),post.getUsrID(),post.getData());
                        resp.add(insert);

                        sub.setDataP(parent.getData());
                        sub.setNumR(x);
                        sub.setRespostas(resp);

                        info.put(postID,sub);
                    }
                }
            }
            else
            {
                postID = post.getID();

                if(!info.containsKey(postID))
                {
                    postXusr sub = new postXusr();

                    sub.setDataP(post.getData());

                    info.put(postID,sub);
                }
            }
        }

        System.out.println("Extra Post Parse Over");

        return info;
    }
}
