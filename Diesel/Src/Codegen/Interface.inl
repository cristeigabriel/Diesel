template <typename T, typename... Args>
void CInterface::pushFunction( std::string const &name, Args&&... args )
{
	if( m_functions.contains( name ) )
		return;

	m_functions[ name ] = std::make_unique<T>( std::forward<Args>( args )... );
}