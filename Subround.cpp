module subround;
import user;


Subround::Subround()
{

}

Subround::Subround(const user::User& painter, const std::vector<user::User>& guessers)
	: m_painter(painter), m_guessers(guessers)
{
}

const user::User& Subround::getPainter() const
{
	return m_painter;
}

void Subround::setPainter(const user::User& painter)
{
	m_painter = painter;
}

const std::vector<user::User>& subround::Subround::getGuessers() const
{
	return m_guessers;
}

void Subround::setGuessers(const std::vector<user::User>& guessers)
{
	m_guessers = guessers;
}

Subround& subround::Subround::operator=(const Subround& other)
{
	if (this == &other) {
		return *this;
	}
	round::Round::operator=(other);
	m_painter = other.m_painter;
	m_guessers = other.m_guessers;
	return *this;
}

subround::Subround::Subround(Subround&& other) noexcept
{
	m_painter = std::move(other.m_painter);
	m_guessers = std::move(other.m_guessers);
}

Subround& subround::Subround::operator=(Subround&& other) noexcept
{
	if (this == &other) {
		return *this;
	}
	round::Round::operator=(std::move(other));
	m_painter = std::move(other.m_painter);
	m_guessers = std::move(other.m_guessers);
	return *this;
}
