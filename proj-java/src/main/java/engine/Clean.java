package engine;

import common.Community;

public class Clean {

  public void clear()
  {
    Community.infoUsers = null;
    Community.infoPosts = null;
    Community.tags = null;
    Community.posts_of_user = null;
    Community.answers_of_question = null;
  }
}
