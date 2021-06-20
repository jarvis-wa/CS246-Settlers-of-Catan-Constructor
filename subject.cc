#include "subject.h"
#include "observer.h"
#include <vector>

Subject::Subject(std::string t, int p): type{t}, pos{p}{}

void Subject::attach(Observer* o) noexcept {
    observers.emplace_back(o);
}

void Subject::notifyObservers() noexcept {
    for (auto &ob : observers) ob->notify( *this );
}

std::string Subject::returnType() noexcept {
    return this->type;
}

int Subject::returnPos() noexcept {
    return this->pos;
}
