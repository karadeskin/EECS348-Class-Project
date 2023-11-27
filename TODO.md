## High Priority

- Class to handle Inja Templating
  - `load` - Load and store files in the class
  - `render` - Render an HTML page by passing data in a JSON

- HTML pages for the website
  - Welcome/main page
    - Header that has create account/log in button
    - link to user page if user is logged in
    - link to calculator
  - User profile page
    - Allows user to delete account for now, maybe ability to add email or personal details the user decides to provide
  - Calculator page
    - Lets user write function in an HTML form and evaluate

- Auth service
  - Create new users
  - Check login information
  - Generate session token
  - Return user from session token

- Calculator service
  - Interface to the calculator part of the app

## Lower Priority

- Script service
  - Look up a script from the scripts db
  - Add a new script to the scripts db
  - Evaluate a script from input passed as a JSON (probably)
