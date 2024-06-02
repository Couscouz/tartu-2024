# 2024 Homework 1 

Please submit your report to secprog at cyber dot ee by March 27th 2024, 23:59 (EET). 

## Task

**Description:**

Your school uses a Python Flask API for managing the grades of students. The security model for the API specifies that all teachers have admin access to the API for modifying grades, students should only be able to look at their arithmetical average grade.

However, recently there have been complaints from teachers, that some students have been able to add and remove their own grades as well. See if you can find a way to alter your grades with a student account, make note of any vulnerabilities discovered in the process and write a formal report that could be sent to the school's IT specialist.

**Expected output:**

A formal report, that

* shortly summarizes, which approaches you tried (what worked and what did not);
* describe the methodology and tools that you used;
* provides a Proof-of-Concept (PoC) for adding/removing grades using a student account, this can be a set of requests or a PoC script with explanations. We need to be sure that you understand the vulnerability that you exploit. In this part, it is mandatory to feature screenshots from your actual penetration testing process;
* any other vulnerabilities or bad coding practices that you discovered during the process and that are relevant to the application. Do keep in mind, that there may be more than one way to exploit the application :)

Use the report template as a basis, you can write the report with whatever you prefer, but you will **need to submit a PDF!**

## Usage

* Install [Docker](https://docs.docker.com/engine/install/);
* unzip the application files;
* navigate to the correct directory;
* run the application with:

```bash
docker compose up -d
```

Navigate to `http://localhost:8080/apidocs` for the Swagger, which specifies all requests.

There are 4 predefined testing accounts:

```
teacher@example.com:adminpass789
student1@example.com:password123
student2@example.com:securepass456
student3@example.com:letmein2022
```
