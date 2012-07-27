#ifndef DEF_RESSOURCESMANAGER
#define DEF_RESSOURCESMANAGER

#include <iostream>
#include <map>

namespace traits
{

template <typename T>
struct clean
{
	static void release(T const& v)
	{

	}
};

template <typename T>
struct clean<T*>
{
	static void release(T * v)
	{
		if(v)
			delete v;
		v = NULL;
	}
};

template <typename T>
struct clean_array
{
	static void release(T * v)
	{
		delete[] v;
	}
};

}

template <typename T, typename CT = traits::clean<T> >
class RessourcesManager
{
	typedef std::string keyType;
	typedef CT cleanning_traits;
public:
	RessourcesManager();
	~RessourcesManager();

	void add(const std::string &name, const T &type);
	void remove(const std::string &name);
	void remove(T &ressource);
	T &get(const std::string &name);
	const std::string &get(const T &ressource) const;
	bool existe(const std::string &name) const;
	
	void clean();

	int getSize() const;
protected:
	std::map <std::string, T> m_ressources;
	typename std::map<std::string, T>::iterator it;
};

template <typename T, typename CT>
inline RessourcesManager<T, CT>::RessourcesManager()
{

}

template <typename T, typename CT>
inline RessourcesManager<T, CT>::~RessourcesManager()
{
	for(auto & p : m_ressources)
		CT::release(p.second);
}

template <typename T, typename CT>
inline void RessourcesManager<T, CT>::add(const std::string &name, const T &type)
{
	if(m_ressources.find(name) == m_ressources.end())
		m_ressources.insert(std::make_pair(name, type));
}

template <typename T, typename CT>
inline void RessourcesManager<T, CT>::remove(const std::string &name)
{
	if(existe(name))
		CT::release(m_ressources[name]);
}

template <typename T, typename CT>
inline void RessourcesManager<T, CT>::remove(T &ressource)
{
	for(typename std::map<std::string, T>::iterator it = m_ressources.begin(); it != m_ressources.end(); ++it)
		if(it == &ressource)
			cleanning_traits::release(*it);
}

template <typename T, typename CT>
inline T &RessourcesManager<T, CT>::get(const std::string &name)
{
	return m_ressources.find(name)->second;
}

template <typename T, typename CT>
inline void RessourcesManager<T, CT>::clean()
{
	for(auto & p : m_ressources)
		CT::release(p.second);
}

template <typename T, typename CT>
inline const std::string  &RessourcesManager<T, CT>::get(const T &ressource) const
{
	for(typename std::map<std::string, T>::iterator it=m_ressources.begin(); it != m_ressources.end(); ++it)
		if(it == &ressource)
			return it->first;
	
	std::cout << "The ressource isn't in this RessourceManager. This function return an \"Error\"\'s std::string" << std::endl;
	return "Error";
}

template <typename T, typename CT>
inline bool RessourcesManager<T, CT>::existe(const std::string &name) const
{
	if(m_ressources.find(name) == m_ressources.end())
		return false;
	return true;
}

template <typename T, typename CT>
inline int RessourcesManager<T, CT>::getSize() const
{
	return m_ressources.size();
}

#endif
