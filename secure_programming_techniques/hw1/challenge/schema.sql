DROP TABLE IF EXISTS users;
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    email TEXT NOT NULL,
    password TEXT NOT NULL,
    isadmin BOOLEAN NOT NULL
);

DROP TABLE IF EXISTS grades;
CREATE TABLE grades (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    grade INTEGER NOT NULL,
    subject TEXT NOT NULL,
    description TEXT NOT NULL,
    user_id INTEGER NOT NULL
);

DROP TABLE IF EXISTS subjects;
CREATE TABLE subjects (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    subject TEXT NOT NULL,
    teacher TEXT NOT NULL
);


INSERT INTO users (email, password, isadmin) VALUES
    ('student1@example.com', 'pbkdf2:sha256:260000$PFaHBD93SVGarXVB$4e39c389442ce5b84ff44c8c80100744b3f5625161377926adde4421add3ef3a', false), -- password123
    ('student2@example.com', 'pbkdf2:sha256:260000$Fu8uh9M5PTfgjdVl$00c63cf56543b9a22e0c6472a28081ec35fe591b22bba76160ff346dd6b4dd52', false), -- securepass456
    ('teacher@example.com', 'pbkdf2:sha256:260000$zIaqPP0Y86NoSlZc$bd503168b9826cca9683275f07a1240b3184fe46d8bc330a507bf6f9fef9bcfb', true), -- adminpass789
    ('student3@example.com', 'pbkdf2:sha256:260000$RF4gakKKRUqbTdaC$70e954f23dc3559a6ab9e449e96600f61e6cb35601c6f9f4ec7e2602843b7231', false); -- letmein2022



INSERT INTO subjects (subject, teacher) VALUES
    ('Mathematics', 'Mr. Johnson'),
    ('English', 'Ms. Smith'),
    ('Science', 'Dr. Rodriguez'),
    ('History', 'Mrs. Thompson'),
    ('Computer Science', 'Mr. Davis');


INSERT INTO grades (grade, subject, description, user_id) VALUES
    (4, 1, 'Excellent performance in Mathematics', 1),
    (3, 2, 'Good understanding of English literature', 2),
    (5, 3, 'Outstanding achievements in Science experiments', 2),
    (2, 4, 'Needs improvement in History knowledge', 4),
    (4, 5, 'Solid understanding of Computer Science concepts', 1),
    (3, 1, 'Consistent performance in Mathematics', 2),
    (5, 2, 'Exceptional skills in English writing', 4),
    (1, 3, 'Struggling with basic Science concepts', 4),
    (4, 4, 'Strong grasp of historical events', 1),
    (2, 5, 'Requires more practice in programming', 2);

