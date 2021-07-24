# CSE102 Term Project Part 2

## Outputs
    - When you run the code, you get .eps files according to contents of 
      "defaults.txt" and "commands.txt" files.
    - Screenshots of some .eps files(considering default txt files) are below.

> #### 1) sq1.eps
![sq1](https://user-images.githubusercontent.com/82276848/126853616-7ab4059d-605e-4484-8367-e21a18c21130.PNG)

> #### 2) hex2.eps
![hex2](https://user-images.githubusercontent.com/82276848/126853627-16d49d93-7e5a-4b9e-8968-9b725c2dbe6d.PNG)

> #### 3) sqs.eps

_Produce an error because there is no described archetype._

![sqs](https://user-images.githubusercontent.com/82276848/126853630-f9e50417-e2b5-4f46-9f09-c7e42984ea5f.PNG)

> #### 4) def.eps
![def](https://user-images.githubusercontent.com/82276848/126853633-93d44f82-e8aa-4dfa-a42d-9b3460ee244c.PNG)

> #### 5) def2.eps
_Can read data from txt file but gives an incorrect output_ :cry: :cry: :cry:

---
> Running the test file:

`$ make -f makefile`

> If there is something wrong, please try this commands:

`$ gcc main.c vectorlib.c -lm -o main`

`$ ./main`

> Notes:

1) When I tried to convert EPS files to PDF format and also used Adobe Illustrator, 
  I failed. Please use "inkscape" or "document viewer" on Ubuntu, if you have a
  problem. 
  
2) I can read hexagon data. I tried but I cannot figure out how to draw hexagon. 
  If you want to draw a hexagon, the program gives you an incorrect output.

> Warning:

    The contents of the "defaults.txt" and "commands.txt" must be similar to
    the files in the folder. You can change data and order of the data but
    the style must remain the same.
    (using of comma, colon, space, parentheses, new line, etc.)
