#include "User.h"

unsigned User::idGenerator = 0;
User::User(const MyString& firstName, const MyString& lastName, const MyString& email,
	const MyString& username, const MyString& password, Role role)
	:_id(idGenerator++), _firstName(firstName), _lastName(lastName), _email(email),
	_username(username), _password(password) {}

unsigned User::getId() const
{
	return _id;
}
const MyString& User::getFirstName()const
{
	return _firstName;
}
const MyString& User::getLastName()const
{
	return _lastName;
}
const MyString& User::getEmail()const
{
	return _email;
}
const MyString& User::getUsername()const
{
	return _username;
}
const MyString& User::getPassword()const
{
	return _password;
}
Role User::getRole()const
{
	return _role;
}

void User::setFirstName(const MyString& name)
{
	_firstName = name;
}
void User::setLastName(const MyString& name)
{
	_lastName = name;
}
void User::setEmail(const MyString& email)
{
	_email = email;
}
void User::setUsername(const MyString& username)
{
	_username = username;
}
void User::setPassword(const MyString& pass)
{
	_password = pass;
}

void User::getData() const
{
	std::cout << "Identity: " << _firstName << " " << _lastName << std::endl;
	std::cout << "Email: " << _email << std::endl;
}