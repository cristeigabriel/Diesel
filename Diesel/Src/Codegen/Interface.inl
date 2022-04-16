template <class T, class... Args>
void CInterface::pushFunction( std::string const &name, Args&& ...args )
{
	if( m_functions.contains( name ) )
		return;

	m_functions[ name ] = std::make_shared<T>( std::forward<Args>( args )... );
}