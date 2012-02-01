# http://stackoverflow.com/questions/36932/whats-the-best-way-to-implement-an-enum-in-python

#~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Animal:
    DOG=1
    CAT=2

x = Animal.DOG


#~~~~~~~~~~~~~~~~~~~~~~~~~~~

def enum(*sequential, **named):
    enums = dict(zip(sequential, range(len(sequential))), **named)
    return type('Enum', (), enums)

Numbers = enum('ZERO', 'ONE', 'TWO')
Numbers.ZERO

#~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Enum(set):
    def __getattr__(self, name):
        if name in self:
            return name
        raise AttributeError


Animals = Enum(["DOG", "CAT", "Horse"])
print Animals.DOG

#
# Excellent. This can be further improved by overriding __setattr__(self, name, value) and 
# maybe __delattr__(self, name) so that if you accidentally write Animals.DOG = CAT, it won't silently succeed.
#

#~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Animal(object):
    values = ['Horse','Dog','Cat']

    class __metaclass__(type):
        def __getattr__(self, name):
            return Animal.values.index(name)

# Realized later there's another handy advantage.. really fast reverse lookups:

def nameOf(self, i):
    return Animal.values[i]


#~~~~~~~~~~~~~~~~~~~~~~~~~~~

dog, cat, rabbit = range(3)

#or

(Pen, Pencil, Eraser) = range(0, 3)

#Using a range also allows you to set any starting value:

(Pen, Pencil, Eraser) = range(9, 12)

# In addition to the above, if you also require that the items belong to a container of some sort, 
# then embed them in a class:

class Stationary:
    (Pen, Pencil, Eraser) = range(0, 3)


#~~~~~~~~~~~~~~~~~~~~~~~~~~~

ANIMALS = ['cat', 'dog', 'python']

def take_for_a_walk(animal):
    assert animal in ANIMALS

#~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Enumerator(object):
    def __init__(self, name):
        self.name = name

    def __eq__(self, other):
        if self.name == other:
            return True
        return self is other

    def __ne__(self, other):
        if self.name != other:
            return False
        return self is other

    def __repr__(self):
        return 'Enumerator({0})'.format(self.name)

    def __str__(self):
        return self.name

class Enum(object):
    def __init__(self, *enumerators):
        for e in enumerators:
            setattr(self, e, Enumerator(e))
    def __getitem__(self, key):
        return getattr(self, key)

class Cow(object):
    State = Enum(
        'standing',
        'walking',
        'eating',
        'mooing',
        'sleeping',
        'dead',
        'dying'
    )
    state = State.standing

#~~~~~~~~~~~~~~~~~~~~~~~~~~~

