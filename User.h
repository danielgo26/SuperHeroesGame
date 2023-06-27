#pragma once
#include "MyString.h"
#include "Enums.h"
class User
{
	static unsigned idGenerator;
	unsigned _id;
	MyString _firstName;
	MyString _lastName;
	MyString _email;
	MyString _username;
	MyString _password;
	Role _role;
public:
	User() = default;
	User(const MyString& firstName, const MyString& lastName, const MyString& email,
		const MyString& username, const MyString& password, Role role);

	unsigned getId() const;
	const MyString& getFirstName()const;
	const MyString& getLastName()const;
	const MyString& getEmail()const;
	const MyString& getUsername()const;
	const MyString& getPassword()const;
	Role getRole()const;

	void setFirstName(const MyString& name);
	void setLastName(const MyString& name);
	void setEmail(const MyString& email);
	void setUsername(const MyString& username);
	void setPassword(const MyString& pass);

	void getData() const;
};