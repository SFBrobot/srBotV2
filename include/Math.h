class math {
  public: int abs(int input) {
    if(input < 0)
      return -input;
    else
      return input;
  }

  double abs(double input) {
    if(input < 0)
      return -input;
    else
      return input;
  }

  int sgn(int input) {
    if(input > 0)
      return 1;
    else if(input < 0)
      return -1;
    else
      return 0;
  }

  int sgn(double input) {
    if(input > 0)
      return 1;
    else if(input < 0)
      return -1;
    else
      return 0;
  }

  int round(double input) {
    if((input - (int)input) >= 0.5)
      return (int)input + 1;
    else
       return (int)input;
  }

};

math Math;
