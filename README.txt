Description:

This program is a password checker program that checks how strong is the entered password. 

The password checker have seven rules to evaluate the vulnerability of the given password:
1. The selected password must be at least eight characters long.
2. The selected password must have at least one uppercase letter.
3. The selected password must have at least one lowercase letter.
4. The selected password must have at least one digit.
5. The selected password must have at least one of these special characters: @, !, #, ^, &, *, or $.
6. The program has also access to a list of previously leaked passwords and should reject if the
   entered password is already leaked with respect to the list.
7. The selected password cannot consist of an English word. For example, mybookLet1990! violates
   this rule. A dictionary of words (with at least size of 5) is given. Using shorter English words or 
   using any other words that are not in the file is valid.