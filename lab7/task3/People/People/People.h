#pragma once
#include <string>

class IPerson
{
public:
	virtual ~IPerson() = default;
	virtual std::string GetLastname() const = 0;
	virtual void SetLastname(std::string const& lastname) = 0;
	virtual std::string GetName() const = 0;
	virtual void SetName(std::string const& name) = 0;
	virtual std::string GetMiddlename() const = 0;
	virtual void SetMiddlename(std::string const& name) = 0;
	virtual std::string GetAddress() const = 0;
	virtual void SetAddress(std::string const& name) = 0;
};

class IPupil : public IPerson
{
public:
	virtual ~IPupil() = default;
	virtual std::string GetSchool() const = 0;
	virtual void SetSchool(std::string const& school) = 0;
	virtual std::string GetGrade() const = 0;
	virtual void SetGrade(std::string const& grade) = 0;
};

class ITeacher : public IPerson
{
public:
	virtual ~ITeacher() = default;
	virtual std::string GetSubject() const = 0;
	virtual void SetSubject(std::string const& subject) = 0;
};

class IStudent : public IPerson
{
public:
	virtual ~IStudent() = default;
	virtual std::string GetUniversity() const = 0;
	virtual void SetUniversity(std::string const& university) = 0;
	virtual std::string GetStudentCard() const = 0;
	virtual void SetStudentCard(std::string const& studentCard) = 0;
};

class IAdvancedStudent : public IStudent
{
public:
	virtual ~IAdvancedStudent() = default;
	virtual std::string GetThesis() const = 0;
	virtual void SetThesis(std::string const& thesis) = 0;
};

class IWorker : public IPerson
{
public:
	virtual ~IWorker() = default;
	virtual std::string GetSpeciality() const = 0;
	virtual void SetSpeciality(std::string const& speciality) = 0;
};

template <typename Base>
class CPersonImpl : public Base
{
public:
	CPersonImpl() {};

	CPersonImpl(std::string lastname, std::string name, std::string middlename, std::string address)
		: m_lastname(lastname)
		, m_name(name)
		, m_middlename(middlename)
		, m_address(address)
	{}

	std::string GetLastname() const override
	{
		return m_lastname;
	}
	void SetLastname(std::string const& lastname) override
	{
		m_lastname = lastname;
	}
	std::string GetName() const override
	{
		return m_name;
	}
	void SetName(std::string const& name) override
	{
		m_name = name;
	}
	std::string GetMiddlename() const override
	{
		return m_middlename;
	}
	void SetMiddlename(std::string const& middlename) override
	{
		m_middlename = middlename;
	}
	std::string GetAddress() const override
	{
		return m_address;
	}
	void SetAddress(std::string const& address) override
	{
		m_address = address;
	}
private:
	std::string m_lastname;
	std::string m_name;
	std::string m_middlename;
	std::string m_address;
};

template <typename Base>
class CStudentImpl : public CPersonImpl<Base>
{
public:
	CStudentImpl() {};
	
	CStudentImpl(std::string lastname, std::string name, std::string middlename, std::string address, std::string university, std::string studentCard)
		: m_university(university)
		, m_studentCard(studentCard)
		, CPersonImpl<Base>(lastname, name, middlename, address)
	{}
	
	std::string GetUniversity() const
	{
		return m_university;
	}

	void SetUniversity(std::string const& university)
	{
		m_university = university;
	}

	std::string GetStudentCard() const
	{
		return m_studentCard;
	}

	void SetStudentCard(std::string const& studentCard)
	{
		m_studentCard = studentCard;
	}
private:
	std::string m_university;
	std::string m_studentCard;
};

class CPupil : public CPersonImpl <IPupil>
{
public:
	CPupil() {};

	CPupil(std::string lastname, std::string name, std::string middlename, std::string address, std::string school, std::string grade)
		: m_school(school)
		, m_grade(grade)
		, CPersonImpl(lastname, name, middlename, address)
	{}

	std::string GetSchool() const
	{
		return m_school;
	}
	void SetSchool(std::string const& school)
	{
		m_school = school;
	}
	std::string GetGrade() const
	{
		return m_grade;
	}
	void SetGrade(std::string const& grade)
	{
		m_grade = grade;
	}
private:
	std::string m_school;
	std::string m_grade;
};

class CTeacher : public CPersonImpl <ITeacher>
{
public:
	CTeacher() {};

	CTeacher(std::string lastname, std::string name, std::string middlename, std::string address, std::string subject)
		: m_subject(subject)
		, CPersonImpl(lastname, name, middlename, address)
	{}

	std::string GetSubject() const
	{
		return m_subject;
	}
	void SetSubject(std::string const& subject)
	{
		m_subject = subject;
	}
private:
	std::string m_subject;
};

class CStudent : public CStudentImpl<IStudent>
{
public:
	CStudent() {};

	CStudent(std::string lastname, std::string name, std::string middlename, std::string address, std::string university, std::string studentCard)
		: CStudentImpl(lastname, name, middlename, address, university, studentCard)
	{}
};

class CAdvancedStudent : public CStudentImpl<IAdvancedStudent>
{
public:
	CAdvancedStudent() {};
	
	CAdvancedStudent(std::string lastname, std::string name, std::string middlename, std::string address, std::string university, std::string studentCard, std::string thesis)
		: m_thesis(thesis)
		, CStudentImpl(lastname, name, middlename, address, university, studentCard)
	{}

	void SetThesis(std::string const& thesis)
	{
		m_thesis = thesis;
	}
	std::string GetThesis() const
	{
		return m_thesis;
	}
private:
	std::string m_thesis;
};

class CWorker : public CPersonImpl <IPerson>
{
public:
	CWorker() {};

	CWorker(std::string lastname, std::string name, std::string middlename, std::string address, std::string speciality)
		: m_sreciality(speciality)
		, CPersonImpl(lastname, name, middlename, address)
	{};

	std::string GetSpeciality() const
	{
		return m_sreciality;
	}
	void SetSpeciality(std::string const& speciality)
	{
		m_sreciality = speciality;
	}
private:
	std::string m_sreciality;
};